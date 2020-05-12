'''
retrieval.py

File used to retrieve coronavirus information using API's in its raw, JSON
    format. Uses two different API's to do so.
'''


import requests
import json
import datetime

state_covid19_api_url = "https://covidtracking.com/api/v1/"

'''
Current API Options (API V1)
States Current Values - states/current.json
	to get one state: states/TX/current.json
States Historical Data - states/daily.json
States Information - states/info.json (Links to sources of info)
US Current Values - us/current.json
US Historical Data - us/daily.json
Counties- counties.json (not usable currently)
State Website Screenshots - states/screenshots.json (unused but available)
In the press - press.json
'''


def date_range(start, end, days_back):
    """
    Returns a list of Datetime objects for days between start and end, inclusive
    """
    r = (end + datetime.timedelta(days=1) - start).days
    return [start + datetime.timedelta(days=i) for i in range(r - days_back)]


def get_covid19_dates():
    """
    Returns a list of strings of covid-19 dates since the pandemic began on January 22, 2020
    """
    start = datetime.date(2020, 1, 22)
    end = datetime.date.today()
    dateList = date_range(start, end, 1)
    return [str(date) for date in dateList]


def make_request(url, headers=None):
    '''
    Function to submit a request
            url - url to request from
            headers - headers of the request

    Returns JSON of response
    '''
    if headers == None:
        headers = {}
    response = requests.request(
        "GET", url, headers=headers)
    j = json.loads(response.text)
    if type(j) == dict:
        j = [j]
    return j


def get_us_covid_data(level, time_length, state=None):
    '''
    Function to request Covid data at the state level

    Parameters
            level - world, us, states
            time_length  - daily, current
            state - Name of the state you want
                    If none, will retrieve all state data

    Returns JSON of data
    '''

    url = state_covid19_api_url
    url += level + "/"
    if state != None:
        url += state + "/"
    url += time_length + ".json"
    return make_request(url)


def get_world_data():
    '''
    Function to request Covid data at the world level

    Parameters
            time_length - daily, current

    Returns JSON of data
    '''
    # modify dates for either time string or not

    url = "https://covid-19-coronavirus-statistics.p.rapidapi.com/v1/total"

    # querystring = {"country":"Canada"}

    headers = {
        'x-rapidapi-host': "covid-19-coronavirus-statistics.p.rapidapi.com",
        'x-rapidapi-key': "567026fb0fmshed791801b2ab42fp1072ecjsndf46ba69121e"
    }

    return make_request(url, headers)


def get_press_data():
    '''
    Function to request Covid data at the state level

    Returns JSON of press data
    '''

    url = state_covid19_api_url + "press.json"
    return make_request(url)


def get_covid19_data(level, time_length, state=None, press=False):
    '''
    Master function to request Covid data

    Parameters
            level - world, us, state
            time_length  - daily, current
            state - Name of the state you want
                    If none, will retrieve all state data
            press - true if you want the latest press releases

    Returns JSON of data
    '''
    level = level.lower()
    time_length = time_length.lower()
    if press:
        return get_press_data()
    elif level == "world":
        return get_world_data()
    if level == "state":  # state is just easier to remember to type in
        level = "states"
    return get_us_covid_data(level, time_length, state)
