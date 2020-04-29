from retrieval import *
import datetime

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
    'Wyoming': 'WY'
}

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


class Covid19_World_Node():

    def __init__(self, c_json):
        # c_json = get_covid19_data("world", "current")[0]["data"]
        self.confirmed = c_json["confirmed"]
        self.deaths = c_json["deaths"]
        self.recovered = c_json["recovered"]
        self.population = populations["World"]
        self.percent_infected = round(
            self.confirmed / self.population * 100, 2)
        self.date = str(datetime.date.today())

    def __str__(self):
        print_string = "Statistics for the world:\n"
        print_string += "\tPopulation: {:,}\n".format(self.population)
        print_string += "\tPercent Infected: {}%\n".format(
            self.percent_infected, 2)
        print_string += "\tConfirmed: {:,}\n".format(self.confirmed)
        print_string += "\tDeaths: {:,}\n".format(self.deaths)
        print_string += "\tRecovered: {:,}\n".format(self.recovered)
        print_string += "\tDate: {}\n".format(self.date)
        # print("in ICU: {}").format(self.icu)
        return print_string


class Covid19_USA_Node():

    def __init__(self, c_json):
        # c_json = get_covid19_data("us", "current")[0]
        self.country = "US"
        self.date = c_json["lastModified"][:10]
        self.confirmed = c_json["positive"]
        self.hospitalized = c_json[
            "hospitalizedCurrently"] if "hospitalizedCurrently" in c_json else 0
        self.recovered = c_json["recovered"] if c_json[
            "recovered"] != None else 0
        self.icu = c_json[
            "inIcuCurrently"] if "inIcuCurrently" in c_json else 0
        self.ventilator = c_json[
            "onVentilatorCurrently"] if "onVentilatorCurrently" in c_json else 0
        self.total_tested = c_json["totalTestResults"]
        self.deaths = c_json["death"]
        self.population = populations[self.country]
        self.percent_infected = round(
            self.confirmed / self.population * 100, 2)

    def __str__(self):
        print_string = "Statistics for the {}:\n".format(self.country)
        print_string += "\tPopulation: {:,}\n".format(self.population)
        print_string += "\tPercent Infected: {}%\n".format(
            self.percent_infected, 2)
        print_string += "\tConfirmed: {:,}\n".format(self.confirmed)
        print_string += "\tDeaths: {:,}\n".format(self.deaths)
        print_string += "\tRecovered: {:,}\n".format(self.recovered)
        print_string += "\tCurrently Hospitalized: {:,}\n".format(
            self.hospitalized)
        print_string += "\tCurrently in ICU: {:,}\n".format(self.icu)
        print_string += "\tCurrently on Ventilator: {:,}\n".format(
            self.ventilator)
        print_string += "\tDate: {}\n".format(self.date)
        return print_string


class Covid19_State_Node():

    def __init__(self, c_json):
        self.state = c_json["state"]
        self.date = c_json["dateChecked"][:10]
        self.confirmed = c_json["positive"]
        # self.negative = c_json["negative"]
        # self.hospitalized = c_json["hospitalizedCurrently"]
        self.recovered = c_json["recovered"] if c_json[
            "recovered"] != None else 0
        # self.icu = c_json["inIcuCurrently"]
        self.total_tested = c_json["totalTestResults"]
        self.deaths = c_json["death"]
        self.population = populations[self.state]
        self.percent_infected = round(
            self.confirmed / self.population * 100, 2)

    def retrieve_historical(self):
        if self.historical == None:
            self.historical = []
            history = get_covid19_data("state", "daily", self.state)
            for time in history:
                try:
                    self.historical.append(Covid19_State(time))
                except KeyError:
                    break
        return self.historical

    def __str__(self):
        print_string = "Statistics for {}:\n".format(self.state)
        print_string += "\tPopulation: {:,}\n".format(self.population)
        print_string += "\tPercent Infected: {}%\n".format(
            self.percent_infected, 2)
        print_string += "\tConfirmed: {:,}\n".format(self.confirmed)
        print_string += "\tDeaths: {:,}\n".format(self.deaths)
        print_string += "\tTested: {:,}\n".format(self.total_tested)
        print_string += "\tRecovered: {:,}\n".format(self.recovered)
        print_string += "\tDate: {}\n".format(self.date)
        return print_string

    def print_historical(self):
        for node in self.historical:
            print(node)


class Covid19_Dataset
n = get_covid19_data("us", "current")[0]
usa = Covid19_USA_Node(n)
print(usa)
