# Smart Display API 

## Overview

This server uses pandas data frames in order to hold each user's information. The data frame table, df, has 3 columns, each of type string. Column 1, 'UID', contains the userid. Column 2, 'DIRECT', contains the direction that the user should take. Column 3, 'DISP', will be either '1' or '2' to represent which display the user's current direction should be displayed onto.

This server uses Flask in order to send and recieve data from both the app and the inkplate 10 display's. The information will be recieved and sent in JSON files. 

# Global Variables

1. id_queue = []

id_queue is a queue that contains avaliable userId's.


2. df = pd.DataFrame({'UID':  pd.Series(dtype='str'),
                   'DIRECT': pd.Series(dtype='str'),
                   'DISP':  pd.Series(dtype='str')})

df is a dataframe that holds all of our user information.


# Functions

## Non Route Functions

1. **def generate_ID():**

This function is used to generate userId's. It uses a tripple for loop. Each for loop iterates through all the possibilities of shapes that can be used as a userId. All possibilities of userId's are generated and added to id_queue. The '_' symbol is placed between each shape, making it easy to parse the information. Each for loop continues for 8 iterations each time, as there are 8 different possible shapes that can be used to make up userId's.

2. **def get_string(x):**

This function is used to assist the generate_ID() function. The parameter x contains the number that determines which shape information should be returned. The '.' symbol between characters seperates the characters that distinguish between the shape itself and the shape's color. The character prior to '.' is the shape itself, and the character following the '.' determines if the color will be black or white.

    Here are the shape possibilities:

    Code    |    Symbol
    --------------------------
    C.B     |   Circle Black
    C.W     |   Circle White
    T.B     |   Triangle Black
    T.W     |   Triangle White
    R.B     |   Rectangle Black
    R.W     |   Rectangle White
    D.B     |   Diamond Black
    D.W     |   Diamond White


3. **def add_rows():**

This function was just used for testing.


## Route Functions

1. @app.route('/get_available_id')
   **def get_available_id():**

This functions returns an avaliable userId. It pops from the queue, id_queue, to get the next avaliable userId.

2. @app.route('/clear_old_id', methods=["POST"])
    **def clear_old_id():**

This function deletes a given user's information from the dataframe, df. It indexes this user's information based on the userId. The userId that was just deleted from the table is then added back to id_queue as an avaliable userId. 

3. @app.route('/')
    **def print_all():**

This function will return the all the contents that exist in the dataframe upon being called. 

4. @app.route('/get_direction', methods=["GET"])
    **def get_direction():**

A given ink plate will request the information should be dipslayed on it from this function. All the userIds and directions that are associated with the given display will be collected. This information will then be turned into a JSON and sent to the given display.

5. @app.route('/update_direction', methods=["POST"])
    **def update_direction():**

This function updates the direction and the display for a given userId. If the userId is not yet in the dataframe, the userId, direction, and display are created as a new column and appended to the dataframe.

# How to Run

1. Instal flask with: pip install flask
2. Instal panadas with: pip install pandas
3. Enter your virtual enironment with:
    a. virtualenv env
    b. source env/bin/activate
4. Run the server with: python smart-display-api.py 
