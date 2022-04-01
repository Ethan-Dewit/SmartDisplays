from flask import Flask, request, render_template
import json
import pandas as pd

id_queue = []
df = pd.DataFrame({'UID':  pd.Series(dtype='str'),
                   'DIRECT': pd.Series(dtype='str'),
                   'DISP':  pd.Series(dtype='str')})

app = Flask(__name__)

@app.route('/get_available_id')
def get_available_id():
    return id_queue.pop(0)


@app.route('/clear_old_id', methods=["POST"])
def clear_old_id():
    global df
    
    freed_id = request.args['FREED_ID']
    df = df[df.UID != freed_id]
    
    id_queue.append(freed_id)
    
    return "ID Freed Successfully"

@app.route('/')
def print_all():
    return render_template('df_display.html', tables=[df.to_html(classes='data')], titles=df.columns.values)

@app.route('/get_direction', methods=["GET"])
def get_direction():
    global df
    
    display = request.args['DISPLAY']
    display_df = df.loc[df['DISP'] == display]
    display_df.drop('DISP', axis=1, inplace=True)
    
    return display_df.to_json(orient = 'records')

@app.route('/update_direction', methods=["POST"])
def update_direction():
    global df

    uid = request.args['UID']
    display = request.args['DISPLAY']
    direction = request.args['DIRECT']

    if uid in df['UID'].values:
        df.loc[df.UID == uid, ['DIRECT', 'DISP']] = direction, display
    else:
        temp = pd.DataFrame({'UID':[uid], 'DIRECT':[direction], 'DISP':[display]})
        df = pd.concat([df, temp], ignore_index = True, axis = 0)

    return 'Direction Updated Successfully'

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

if __name__ == '__main__':
    generate_ID()
    #add_rows()
    app.run(debug=True, port=5000)

"""
    receive and interpret JSON in update_direction
    recieve UID and remove column in clear_old_id
"""