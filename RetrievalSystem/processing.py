'''
processing.py

This file does some simple data processing by just extracting the information from the JSON.
    Performed here becaues C has no dictionary datatype and I wanted to just be able to send
    the info I needed to display. Data is collected in ~7 seconds and then is stored for up to
    one hour before being declared stale.

'''
from retrieval import *
import datetime
import pickle
import traceback
import os.path
import time

dataset_save_file = "../Covid19Data/Covid19_Dataset.txt"
last_saved_file = "../Covid19Data/Date_Modified.txt"
dataset_timeout = datetime.timedelta(hours=1)

states = ["AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DC", "DE", "FL", "GA",
          "HI", "ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD",
          "MA", "MI", "MN", "MS", "MO", "MT", "NE", "NV", "NH", "NJ",
          "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC",
          "SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY"]

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

populations = {"World": 7780953897,
               "US": 329579469,
               "AL": 4903185,
               "AK": 731545,
               "AZ": 7278717,
               "AR": 3017804,
               "CA": 39512223,
               "CO": 5758736,
               "CT": 3565287,
               "DC": 705749,
               "DE": 973764,
               "FL": 21477737,
               "GA": 10617423,
               "HI": 1415872,
               "ID": 1787065,
               "IL": 12671821,
               "IN": 6732219,
               "IA": 3155070,
               "KS": 2913314,
               "KY": 4467673,
               "LA": 4648794,
               "ME": 1344212,
               "MD": 6045680,
               "MA": 6892503,
               "MI": 9986857,
               "MN": 5639632,
               "MS": 2976149,
               "MO": 6137428,
               "MT": 1068778,
               "NE": 1934408,
               "NV": 3080156,
               "NH": 1359711,
               "NJ": 8882190,
               "NM": 2096829,
               "NY": 19453561,
               "NC": 10488084,
               "ND": 762062,
               "OH": 11689100,
               "OK": 3956971,
               "OR": 4217737,
               "PA": 12801989,
               "PR": 3193694,
               "RI": 1059361,
               "SC": 5148714,
               "SD": 884659,
               "TN": 6829174,
               "TX": 28995881,
               "UT": 3205958,
               "VT": 623989,
               "VA": 8535519,
               "WA": 7614893,
               "WV": 1792147,
               "WI": 5822434,
               "WY": 578759}


class Covid19_Node():
    '''
    Common class for Covid19 Nodes
    All have:
            self.name
            self.confirmed
            self.deaths
            self.recovered
            self.population
            self.date
            self.percent_infected
    '''

    def __str__(self):
        # Gives a string representation of exactly what we need to send to PSOC
        delim = '\n'
        s = "{}{}".format(
            abbrev_to_name[self.__dict__["name"]], delim)
        s += "{}{}".format(self.__dict__["date"], delim)
        for key, value in self.__dict__.items():
            key = " ".join(key.capitalize().split("_"))
            if type(value) == int:
                s += "{}{}{:,}{}".format(key, delim, value, delim)
            elif "Percent" in key or "rate" in key:
                if "rate" not in key:
                    key = key.split()  # [percent, characteristic]
                    # % characteristic, to fit on screen
                    key = "% " + key[1].capitalize()
                s += "{}{}{}%{}".format(key, delim, value, delim)
            elif key == "Name" or key == "Date":
                continue
            else:
                s += "{}{}{}{}".format(key, delim, value, delim)
        s += "END".format(delim)
        return s

    def __repr__(self):
        # just for nice display in dictionaries :-)
        return "{}-{}".format(self.__dict__["name"], self.__dict__["date"])


# All Node classes only have an init function where the datatypes are stored for
#   later transmission.
class Covid19_World_Node(Covid19_Node):
    '''
    Class to represent one date status of the world in regards to coronavirus

    '''

    def __init__(self, c_json):
        self.name = "WORLD"
        self.date = str(datetime.date.today())
        self.population = populations["World"]
        self.confirmed = c_json["confirmed"]
        self.deaths = c_json["deaths"]
        self.recovered = c_json["recovered"]
        self.active = self.confirmed - self.deaths - self.recovered
        self.percent_infected = round(
            self.confirmed / self.population * 100, 2)
        self.percent_recovered = round(
            self.recovered / self.confirmed * 100, 2)
        self.death_rate = round(self.deaths / self.confirmed * 100, 2)
        self.percent_active = round(self.active / self.confirmed * 100, 2)


class Covid19_USA_Node(Covid19_Node):

    def __init__(self, c_json):
        self.name = "US"
        try:
            self.date = c_json["lastModified"][:10]
        except KeyError:
            self.date = c_json["dateChecked"][:10]
        self.population = populations[self.name]
        self.confirmed = c_json["positive"] if c_json[
            "positive"] != None else 0
        self.total_tested = c_json["totalTestResults"]
        self.recovered = c_json["recovered"] if c_json[
            "recovered"] != None else 0
        # self.in_icu = c_json[
        #    "inIcuCurrently"] if "inIcuCurrently" in c_json else 0
        self.deaths = c_json["death"] if c_json["death"] != None else 0
        self.active = self.confirmed - self.deaths - self.recovered
        self.hospitalized = c_json[
            "hospitalizedCurrently"] if "hospitalizedCurrently" in c_json else 0
        self.on_ventilator = c_json[
            "onVentilatorCurrently"] if "onVentilatorCurrently" in c_json else 0
        self.percent_infected = round(
            self.confirmed / self.population * 100, 2)
        self.percent_tested = round(
            self.total_tested / self.population * 100, 2)

        if self.confirmed != 0:
            self.percent_recovered = round(
                self.recovered / self.confirmed * 100, 2)
            self.death_rate = round(self.deaths / self.confirmed * 100, 2)
            self.percent_active = round(self.active / self.confirmed * 100, 2)
        else:
            self.percent_recovered = round(0, 2)
            self.death_rate = round(0, 2)
            self.percent_active = round(0, 2)


class Covid19_State_Node(Covid19_Node):

    def __init__(self, c_json):
        self.name = c_json["state"]
        self.date = c_json["dateChecked"][:10]
        self.population = populations[self.name]
        self.confirmed = c_json["positive"] if c_json[
            "positive"] != None else 0
        self.total_tested = c_json["totalTestResults"]
        self.recovered = c_json["recovered"] if c_json[
            "recovered"] != None else 0
        self.deaths = c_json["death"] if c_json["death"] != None else 0
        self.active = self.confirmed - self.deaths - self.recovered

        self.percent_infected = round(
            self.confirmed / self.population * 100, 2)
        self.percent_tested = round(
            self.total_tested / self.population * 100, 2)

        if self.confirmed != 0:
            self.percent_recovered = round(
                self.recovered / self.confirmed * 100, 2)
            self.death_rate = round(self.deaths / self.confirmed * 100, 2)
            self.percent_active = round(self.active / self.confirmed * 100, 2)
        else:
            self.percent_recovered = round(0, 2)
            self.death_rate = round(0, 2)
            self.percent_active = round(0, 2)


class Covid19_Press():
    # Not used currently, but available if wanted.

    def __init__(self):
        press_list = get_covid19_data("", "", press=True)
        self.press = []
        for article in press_list:
            self.press.append(Covid19_Article(article))

    def __str__(self):
        s = ""
        for i, article in enumerate(self.press):
            s += "{}. {}".format(i, str(article))
        return s


class Covid19_Article():
    # Not used currently, but available if wanted.

    def __init__(self, article_json):
        self.title = article_json[
            "title"] if article_json["title"] != None else "No Title"
        self.url = article_json["url"]
        self.published_date = article_json["publishDate"]
        self.publisher = article_json["publication"]
        self.author = article_json[
            "author"] if "author" in article_json else "Unknown Author"

    def __str__(self):
        return "{}\n\tPublished on {} at {} by {}\n\tLink to article: {}\n".format(self.title, self.published_date, self.publisher, self.author, self.url)

    def __repr__(self):
        return self.title


class Covid19_Dataset():
    '''
        Class that maintains the whole dataset, it tries to load from storage, but creates and saves
            if not available. 

        Methods:
            save() - saves the whole dataset to a priorly specified file
            load() - attempts to load the dataset
            get_all_current() - gets all current data for all nodes in the dataset
            get_current(name) - gets the current data for the specified node
            get_by_date(name, month, day) - gets the data for a specific node for
                                              a specific data
            get_all_historical(name) - returns all historical information currently
                                        stored
            get_historical(name, save=False) - gets historical information for name,
                                                optionally saves the dataset if changes are made
            def retrieve_historical(name) - static method used to actually obtain the historical
                                              data by creating a list of nodes

    '''

    def __init__(self):
        try:
            self.load()
        except:
            print("Couldn't load, generating new")
            self.names = states
            self.current = {state_data["state"]: Covid19_State_Node(
                state_data) for state_data in get_covid19_data("states", "current") if state_data["state"] in states}
            self.current["US"] = Covid19_USA_Node(
                get_covid19_data("us", "current")[0])
            self.current["WORLD"] = Covid19_World_Node(
                get_covid19_data("world", "current")[0]["data"])
            self.press = Covid19_Press()
            self.history = {state: {} for state in self.names}
            self.history["US"] = {}
            for state in self.history:
                self.get_historical(state)
            self.save()

    def save(self):
        # save file
        data_file = open(dataset_save_file, 'wb')
        data_file.write(pickle.dumps(self.__dict__))
        data_file.close()

        # save time saved, so data doesn't get too stale
        time_file = open(last_saved_file, "w")
        time_file.write(str(datetime.datetime.now()).split(".")[0])

        print("Dataset saved at {}".format(datetime.datetime.now()))

    def load(self):
        # load time and check if stale
        time_file = open(last_saved_file, "r")
        last_saved = time_file.read()
        time_file.close()
        modify_time = datetime.datetime.strptime(
            last_saved, "%Y-%m-%d %H:%M:%S")
        time_since_modify = datetime.datetime.now() - modify_time
        if time_since_modify > dataset_timeout:
            raise RuntimeError  # will now be reloaded instead

        # if recent enough, read the file
        file = open(dataset_save_file, "rb")
        dataPickle = file.read()
        file.close()

        self.__dict__ = pickle.loads(dataPickle)
        print("Successfully loaded Covid-19 Dataset")

    def get_all_current(self):
        return self.current

    def get_current(self, name):
        return self.current[name]

    def get_by_date(self, name, month, day):
        history = self.get_historical(name)
        # make the data string
        date_string = "2020-"
        if len(month) < 2:
            date_string += "0"
        date_string += month
        date_string += "-"
        if len(day) < 2:
            date_string += "0"
        date_string += day

        # search for that day
        for day in history:
            if day.date == date_string:
                return day
        # otherwise day does not exist, raise error
        raise KeyError

    def get_all_historical(self, name):
        """
        returns all available historical data
        """
        return self.history

    def get_historical(self, name, save=False):
        if len(self.history[name]) == 0:
            self.history[name] = Covid19_Dataset.retrieve_historical(name)
            if save:
                self.save()
        return self.history[name]

    @staticmethod
    def retrieve_historical(name):
        historical = []
        name = name.lower()
        # assign the correct level
        level = "state"
        if name == "world":
            level = "world"
        elif name == "us":
            level = "us"
            name = None

        # retrieve the history
        history = get_covid19_data(level, "daily", name)

        # pick which class to make
        if level == "world":
            Make_Node = Covid19_World_Node
        elif level == "us":
            Make_Node = Covid19_USA_Node
        else:
            Make_Node = Covid19_State_Node

        # add nodes to the history
        for time in history:
            try:
                historical.append(Make_Node(time))
            except KeyError:

                break
        return historical


if __name__ == "__main__":
    data = Covid19_Dataset()
