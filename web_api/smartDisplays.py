import numpy as np
import pandas as pd
from sklearn import cluster
import matplotlib.pyplot as plt
import json
 
class smartDisplays():

        # userId Meanings:
         # w = white
         # b = black
         # t = triangle
         # c = circle
         # r = rectangle

    def main():

        # DataFrame for testing
        # df should include userID, direction, display, and time
        df = pd.DataFrame({'UID':    ['w.c_w.c_w.c', 'b.c_b.c_b.c', 'w.t_w.t_w.t', 'b.t_b.t_b.t'],
                            'DIRECT':  ['right', 'up', 'left', 'down'],
                            'DISP':    ['1', '2', '2', '1']})

        
        # TEST FOR READING USER INFROMATION TO DF
        # (should get this information from JSON)

        # Parse user infromation from JSON
        curUser = 'w.c_w.c_w.t'
        curDirect = 'left'
        curDisplay = '2'

        # Create a new row with userInfo
        newCol = pd.DataFrame({ 'UID':    [curUser],
                                'DIRECT':  [curDirect],
                                'DISP':    [curDisplay]})



        # userExists will be true if user exists in df and false otherwise
        userExists = df.isin([curUser]).any().any()

        # If the user is already in df
        if userExists:
            # replace that userId's row with newCol (contains updated information)
            df.loc[df['UID'] == curUser] = newCol
        else:
            # add column with their information
            df = df.append(newCol)
                
        # TESTING: print(df)

    # Get an avaliable userID for a new user
    def get_available_id(self, userId):
        # put userIds in a queue
        # start with 10 constant userIds in df for testing
        # iterate through shapes in a for loop to generate userIds
       
       
    # Clear out any ideas that don't need more directions
    def clear_old_id(self, userId):


    # get json information from the app
    def receive_direction_info(self, userId, direction):


    # send updated user information 
    def send_direction(self, userId):
                
           
    if __name__ == "__main__":
        main()
