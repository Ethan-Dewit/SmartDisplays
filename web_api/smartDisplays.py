from flask import Flask, request, render_template
import json
import pandas as pd
pd.options.mode.chained_assignment = None  # default='warn'

id_queue = []
df = pd.DataFrame({'UID':  pd.Series(dtype='str'),
                   'DIRECT': pd.Series(dtype='str'),
                   'ORDER': pd.Series(dtype='str'),
                   'DISP':  pd.Series(dtype='str')})

app = Flask(__name__)

#returns a new available id
@app.route('/get_available_id')
def get_available_id():
    global df

    uid = id_queue.pop(0)
    
    temp = pd.DataFrame({'UID':[uid], 'ORDER':['0'], 'DIRECT':[None], 'DISP':[None]})
    df = pd.concat([df, temp], ignore_index = True, axis = 0)

    temp = pd.DataFrame({'UID':[uid], 'ORDER':['1'], 'DIRECT':[None], 'DISP':[None]})
    df = pd.concat([df, temp], ignore_index = True, axis = 0)

    return uid

#clears an ID in use from the DF table
#param: String FREED_ID
@app.route('/clear_old_id', methods=["POST"])
def clear_old_id():
    global df
    
    freed_id = request.args['FREED_ID']
    df = df[df.UID != freed_id]
    
    id_queue.append(freed_id)
    
    return "ID Freed Successfully"
#base route, shows all ID's currently in DF
@app.route('/')
def print_all():
    return render_template('df_display.html', tables=[df.to_html(classes='data')], titles=df.columns.values)

#Called by display, returns all UID/Direction combos to specified display
#PARAM: String DISPLAY
@app.route('/get_direction', methods=["GET"])
def get_direction():
    global df
    
    display = request.args['DISPLAY']
    display_df = df.loc[df['DISP'] == display]
    display_df.drop('DISP', axis=1, inplace=True)
    display_df.drop('ORDER', axis=1, inplace=True)
    
    return display_df.to_json(orient = 'records')

#Adds/changes direction associated wiht a certain UID
#param: String UID_0, ORDER_0, DISPLAY_0, DIRECT_0, UID_1, ORDER_1, DISPLAY_1, DIRECT_1
#ORDER_0 should always be 0, ORDER_1 should always be 1
#UID_0 and UID_1 should always match
@app.route('/update_direction', methods=["POST"])
def update_direction():
    global df

    uid_0 = request.args['UID_0']
    order_0 = request.args['ORDER_0']
    display_0 = request.args['DISPLAY_0']
    direction_0 = request.args['DIRECT_0']
    uid_1 = request.args['UID_1']
    order_1 = request.args['ORDER_1']
    display_1 = request.args['DISPLAY_1']
    direction_1 = request.args['DIRECT_1']

    if (not uid_0 in df['UID'].values) and (not order_0 in df['ORDER']):
        return 'Could not find UID'
    if (not uid_1 in df['UID'].values) and (not order_1 in df['ORDER']):
        return 'Could not find UID'

    df.loc[(df.UID == uid_0) & (df.ORDER == order_0), ['DIRECT', 'DISP']] = direction_0, display_0
    df.loc[(df.UID == uid_1) & (df.ORDER == order_1), ['DIRECT', 'DISP']] = direction_1, display_1

    return 'Direction Updated Successfully'

#helper function used to generate UIDs
def get_string(x):
    if x == 0:
        return 'C.B'
    elif x == 1:
        return 'C.W'
    elif x == 2:
        return 'T.B'
    elif x == 3:
        return 'T.W'
    elif x == 4:
        return 'R.B'
    elif x == 5:
        return 'R.W'
    elif x == 6:
        return 'D.B'
    elif x == 7:
        return 'D.W'

#function used to generate UIDs
def generate_ID():
    string_range = 8
    for i in range(string_range):
        first = get_string(i)
        for j in range(string_range):
            second = get_string(j)
            for k in range(string_range):
                third = get_string(k)

                uid = first  + '_' + second + '_' + third
                id_queue.append(uid)

def add_rows():
    global df   #Allows access to global variable df

    df1 = pd.DataFrame({'UID':[id_queue.pop(0)], 'DIRECT':['right'], 'DISP':['1']})
    df2 = pd.DataFrame({'UID':[id_queue.pop(0)], 'DIRECT':['left'], 'DISP':['2']})
    df3 = pd.DataFrame({'UID':[id_queue.pop(0)], 'DIRECT':['up'], 'DISP':['2']})
    df4 = pd.DataFrame({'UID':[id_queue.pop(0)], 'DIRECT':['down'], 'DISP':['1']})

    df = pd.concat([df, df1], ignore_index = True, axis = 0)
    df = pd.concat([df, df2], ignore_index = True, axis = 0)
    df = pd.concat([df, df3], ignore_index = True, axis = 0)
    df = pd.concat([df, df4], ignore_index = True, axis = 0)

#Need to set host="0.0.0.0" to run on server
if __name__ == '__main__':
    generate_ID()
    #add_rows()
    app.run(debug=True, port=5000)
