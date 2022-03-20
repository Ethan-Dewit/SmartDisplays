import numpy as np
import pandas as pd
from sklearn import cluster
import matplotlib.pyplot as plt


class smartDisplays():

    def __init__(self):
    # Recieving this in a json file
    # hosting a pandas df on a task application

    # put userIds in a queue
    # start with 10 constant userIds in df for testing
    # iterate through shapes in a for loop to generate userIds
    # df should include userID, direction, display, and time


    # Get userID from app and store in a dataframe
    def get_available_id(self, userId):
        # change userID symbols at some point
        

    # Clear out any ideas that don't need more directions
    # Set a time limit from the last time each idea was used
    def clear_old_id(self, userId):


    # app sends info to our python app
    # send the direction to go in to display
    def receive_direction_info(self, userId, direction):


    # the tablet we call
    # tablet going to
    def send_direction(self, userId):
        # return direction
