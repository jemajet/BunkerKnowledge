from retrieval import *

"""
Only testing get covid 19 data function
Parameters:
    level (3 vals) - world, us, state
    time_length (2 vales) - daily, current
    state (50 possible, only check 1) - TX, etc.
    press (1 val, different case) - true

"""

states = ["AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DC", "DE", "FL", "GA",
          "HI", "ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD",
          "MA", "MI", "MN", "MS", "MO", "MT", "NE", "NV", "NH", "NJ",
          "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC",
          "SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY"]


def test_response(response):
    try:
        if type(response[0]) == dict and len(response) == 1:
            r = len(list(response[0].keys()))
        if type(response) == list:
            r = len(response)
        if r > 0:
            return True
        else:
            return False
    except:
        return False


def print_test_result(string, result):
    if result:
        print("Test {}: Passed".format(string))
    else:
        print("Test {}: Failed".format(string))


def world_test():
    r = get_covid19_data("world", "current")
    result = test_response(r)
    print_test_result("World Data", result)
    return result


def states_current_test():
    r = get_covid19_data("state", "current", "TX")
    result = test_response(r)
    print_test_result("state current (TX)", result)
    return result


def states_daily_test():
    r = get_covid19_data("state", "daily", "TX")
    result = test_response(r)
    print_test_result("state daily (TX)", result)
    return result


def press_test():
    r = get_covid19_data(None, None, press=True)
    result = test_response(r)
    print_test_result("press data", result)
    return result


def test_covid19_data_retrieval():
    r = world_test()
    r = states_current_test() and r
    r = states_daily_test() and r
    r = press_test() and r
    if r:
        print("All tests passed! :)")
    else:
        print("Some tests failed! :(")

if __name__ == "__main__":
    test_covid19_data_retrieval()
