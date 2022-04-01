import requests
import pandas as pd

base_url = "http://127.0.0.1:5000"
get_uid_url = "/get_available_id"
get_direct_url = "/get_direction"
free_id_url = "/clear_old_id"
update_direct_url = "/update_direction"


def get_uid():
	my_url = base_url + get_uid_url
	r = requests.get(my_url)
	print(r.text)
	return r.text

def get_directions(display_id):
	print("getting instructions for display: " , display_id)

	PARAMS = {'DISPLAY':display_id}
	my_url = base_url + get_direct_url

	r = requests.get(url = my_url, params = PARAMS)

	df = pd.DataFrame.from_dict(r.json())
	print(df.head(), '\n')

def free_id(freed_id):
	PARAMS = {'FREED_ID':freed_id}
	my_url = base_url + free_id_url

	r = requests.post(url = my_url, params = PARAMS)
	print(r.text, '\n')

def update_direct(uid, direct, disp):
	print("updating API with service with uid: " , uid , " direction: " , direct, " display: ", disp)

	my_url = base_url + update_direct_url
	PARAMS = {'UID':uid, 'DISPLAY':disp, 'DIRECT':direct}

	r = requests.post(url = my_url, params = PARAMS)
	print(r.text, '\n')

if __name__ == '__main__':
	uid_1 = get_uid()
	uid_2 = get_uid()
	uid_3 = get_uid()
	update_direct(uid_1, 'left', '1')
	update_direct(uid_2, 'right', '2')
	update_direct(uid_3, 'down', '1')
	get_directions('1')
	get_directions('2')
	update_direct(uid_3, 'up', '2')
	get_directions('1')
	get_directions('2')
	free_id(uid_1)
	free_id(uid_2)
	free_id(uid_3)
	get_directions('1')
	get_directions('2')