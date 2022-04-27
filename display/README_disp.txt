--README--

to run a smart display do the following:

1) download arduinos code editor app

2) follow the steps provided at: 
https://inkplate.io/getting-started/
to set up the board definition and get the
inkplate libraries 

3) download the following libraries using the
arduino editor's library manager.
	- WiFi 
 	- ArduinoHttpClient
	- Arduino_JSON

4) copy or download code for disp.ino and open 
it in arduino's code editor. 

 
5) on lines 37, 38, and 39 there are definitions
of ssid, pass, and serverAddress. edit these to 
be whatever network you are connecting the
inkpalte to and the password to said network. 
make serverAddress whatever ip4 address you are
running the backend api on 

6) plug in the inkplate to your machine, make sure
the board is inkplate10 and the port it correct 
and upload the code to the inkplate

7) once the code is uploaded it should display 
the user ids and directions assigned to display 0
in the backend database. (you can change the 
display number by holding the "3" button to 
increment and the "1" button to decrement, range
of 0-10)



 