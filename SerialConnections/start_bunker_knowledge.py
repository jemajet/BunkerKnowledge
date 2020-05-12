'''
start_bunker_knowledge.py

Main file used, this is the access point into the whole system. It runs
    a MINMON, terminal style interface where commands can be input, sent,
    and displayed on the TFT screen. This is where the baud rate and com
    port can be changed.

'''

import sys
sys.path.insert(1, "../RetrievalSystem")
from processing import *
from retrieval import *
import serial
import time
import threading
from plotly.subplots import make_subplots
import plotly.express as px
import plotly.graph_objects as go
import pandas as pd

us_state_abbrev = {
    'Alabama': 'AL',
    'Alaska': 'AK',
    'American Samoa': 'AS',
    'Arizona': 'AZ',
    'Arkansas': 'AR',
    'California': 'CA',
    'Colorado': 'CO',
    'Connecticut': 'CT',
    'Delaware': 'DE',
    'District of Columbia': 'DC',
    'Florida': 'FL',
    'Georgia': 'GA',
    'Guam': 'GU',
    'Hawaii': 'HI',
    'Idaho': 'ID',
    'Illinois': 'IL',
    'Indiana': 'IN',
    'Iowa': 'IA',
    'Kansas': 'KS',
    'Kentucky': 'KY',
    'Louisiana': 'LA',
    'Maine': 'ME',
    'Maryland': 'MD',
    'Massachusetts': 'MA',
    'Michigan': 'MI',
    'Minnesota': 'MN',
    'Mississippi': 'MS',
    'Missouri': 'MO',
    'Montana': 'MT',
    'Nebraska': 'NE',
    'Nevada': 'NV',
    'New Hampshire': 'NH',
    'New Jersey': 'NJ',
    'New Mexico': 'NM',
    'New York': 'NY',
    'North Carolina': 'NC',
    'North Dakota': 'ND',
    'Northern Mariana Islands': 'MP',
    'Ohio': 'OH',
    'Oklahoma': 'OK',
    'Oregon': 'OR',
    'Pennsylvania': 'PA',
    'Puerto Rico': 'PR',
    'Rhode Island': 'RI',
    'South Carolina': 'SC',
    'South Dakota': 'SD',
    'Tennessee': 'TN',
    'Texas': 'TX',
    'Utah': 'UT',
    'Vermont': 'VT',
    'Virgin Islands': 'VI',
    'Virginia': 'VA',
    'Washington': 'WA',
    'West Virginia': 'WV',
    'Wisconsin': 'WI',
    'Wyoming': 'WY',
    'USA': 'US',
    'World': 'WORLD'
}

abbrev_to_name = {v: k for k, v in us_state_abbrev.items()}


class Serial_Control():

    def __init__(self, port, baud_rate):
        # Loading the dataset can take a while
        print("-Please wait for startup (could take up to 10 seconds)")
        self.dataset = Covid19_Dataset()
        self.port = port
        self.baud_rate = baud_rate
        self.big_board_serial = None
        self.line_reader = None

    def start(self):
        # starts the serial connection and puts us in terminal mode
        self.big_board_serial = serial.Serial(self.port, self.baud_rate)
        self.line_reader = ReadLine(self.big_board_serial)
        self.startup()
        self.terminal()

    def startup(self):
        world_data = str(self.dataset.get_current("WORLD"))
        # send world data to display on startup
        self.send_data(world_data, receipt=False)
        print("\n  ****************************************************************")
        print("  * Welcome to Bunker Knowledge, the Covid-19 Database Terminal! *")
        print("  ****************************************************************\n")

        print("-To get help, please type help\n")

    def terminal(self):
        # terminal MINMON style command checker
        while True:
            command = self.get_command().strip()
            try:
                if command == "exit":
                    # ends the program
                    break
                elif command == "help":
                    # help_file.txt has the what is printed here
                    self.help()
                elif 'graph' in command:
                    # graphs the data for the specified name
                    split_command = command.split(" ")
                    name = " ".join((split_command)[:-1])
                    name = self.clean_name(name)
                    data = str(self.dataset.get_current(name))
                    self.send_data(data)
                    self.graph(name)

                elif len(command.split(" ")) >= 3:
                    # particular date, send that data
                    # [name] [month] [day] is command format
                    split_command = command.split(" ")
                    day = split_command[-1]
                    month = split_command[-2]
                    name = " ".join((split_command)[:-2])
                    name = self.clean_name(name)
                    data = str(self.dataset.get_by_date(name, month, day))
                    self.send_data(data)
                else:
                    # singular name, send data for today's date
                    name = self.clean_name(command)
                    data = str(self.dataset.get_current(name))
                    self.send_data(data)

            except KeyError:
                error = "No data for {}".format(command)
                print(error)
                error += "\nEND\n"
                self.big_board_serial.write(error.encode())

        self.big_board_serial.close()

    def clean_name(self, name):
        # function to take the name of a state and convert it correctly into the stored
        #   two letter postal code
        if len(name) != 2 and name != "world":
            # not using state code
            name = name.split(" ")
            for i, x in enumerate(name):
                name[i] = x.capitalize()  # capitalize multi letter states
            name = " ".join(name)
            name = us_state_abbrev[name]
        name = name.upper()
        return name

    def send_data(self, data, receipt=True):
        # sends the data line by line, and sends the delimiter specified
        #   by the psoc
        data = data.split("\n")
        for dat in data:
            self.big_board_serial.write(dat.encode())
            self.big_board_serial.write("\n".encode())  # delimited
        if receipt:
            print(r'Sent: {}'.format(data))

    def get_command(self):
        # waits for a new command
        return input(" > ").lower()

    def help(self):
        # Prints from my help file command instructions
        help_file = "help_file.txt"
        with open(help_file, "r") as f:
            text = f.read()
            print(text)

    def graph(self, name):
        # graphs the data, was originally intended to be used to send over port, but shifted because of
        #   graphics library limitations
        data = get_timeseries(self.dataset, name)
        df = pd.DataFrame(
            data, columns=["Date", "Confirmed", "Active", "Deaths", "Recovered", "New Cases"])

        # Add data
        fig = make_subplots(rows=1, cols=2)
        name = abbrev_to_name[name]

        # Create and style trace 1, line graphs of info
        fig.add_trace(go.Scatter(x=df["Date"], y=df["Confirmed"], name='Confirmed',
                                 line=dict(color='red', width=4)), row=1, col=1)
        fig.add_trace(go.Scatter(x=df["Date"], y=df["Active"], name='Active',
                                 line=dict(color='orange', width=4)), row=1, col=1)
        fig.add_trace(go.Scatter(x=df["Date"], y=df["Deaths"], name='Deaths',
                                 line=dict(color='black', width=4,)), row=1, col=1)
        fig.add_trace(go.Scatter(x=df["Date"], y=df["Recovered"], name='Recovered',
                                 line=dict(color='green', width=4)), row=1, col=1)

        # Create and style trace 2, bar graph of new cases
        fig.add_trace(go.Bar(x=df["Date"], y=df[
                      "New Cases"], name="Daily New Cases"), row=1, col=2)
        fig.update_layout(title="{} Covid-19 Statistics".format(name),
                          xaxis_title='Date',
                          yaxis_title='Cases')
        fig.show()


def get_timeseries(dataset, name):
    # retrieves the dates, confirmed, active, deaths, and recovered time series from
    # a dataset
    history = dataset.get_historical(name)
    history.reverse()  # already sorted, reverse
    data = {"Date": [], "Confirmed": [],
            "Active": [], "Deaths": [], "Recovered": [], "New Cases": []}
    oldconfirmed = 0
    for date in history:
        data["Date"].append(pd.to_datetime(
            date.date, infer_datetime_format=True))
        data["Confirmed"].append(date.confirmed)
        data["Active"].append(date.active)
        data["Deaths"].append(date.deaths)
        data["Recovered"].append(date.recovered)
        data["New Cases"].append(date.confirmed - oldconfirmed)
        oldconfirmed = date.confirmed
    return data


if __name__ == "__main__":
    port = "COM3"
    baud = 57600
    connection = Serial_Control(port, baud)
    connection.start()
