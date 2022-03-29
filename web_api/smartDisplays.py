from flask import Flask, request, render_template
import json
import pandas as pd

id_queue = []
#df = pd.DataFrame({'UID':  pd.Series(dtype='str'),
#                     'DIRECT': pd.Series(dtype='str'),
#                  'DISP':  pd.Series(dtype='int')})

df = pd.DataFrame({'UID':    ['w.c_w.c_w.c', 'b.c_b.c_b.c', 'w.t_w.t_w.t', 'b.t_b.t_b.t'],
                    'DIRECT':  ['right', 'up', 'left', 'down'],
                    'DISP':    ['1', '2', '2', '1']})

app = Flask(__name__)

@app.route('/get_available_id', methods=["GET"])
def get_available_id():
    return id_queue.pop(0)


@app.route('/clear_old_id', methods=["POST"])
def clear_old_id():
    df = df[df.uid != freed_id]
    id_queue.append(freed_id)

@app.route('/')
def print_all():
    return render_template('df_display.html', tables=[df.to_html(classes='data')], titles=df.columns.values)


@app.route('/get_direction', methods=["GET"])
def get_direction():
    display = '1'
    display_df = df.loc[df['DISP'] == display]
    display_df.drop('DISP', axis=1, inplace=True)
    return display_df.to_json(orient = 'records')

@app.route('/update_direction', methods=["POST"])

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

if __name__ == '__main__':
    generate_ID()
    app.run(debug=True, port=5000)

"""
    recieve display_id to use in get_direction

    receive and interpret JSON in update_direction
    recieve UID and remove column in clear_old_id
"""