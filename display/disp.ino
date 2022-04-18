#include <Inkplate.h>
#include "WiFi.h"
#include <ArduinoHttpClient.h>
#include <Arduino_JSON.h>

#include <vector>
#include <array>

#ifndef DEBUG
#define DEBUG 0
#endif

// This will remove the PDEBUG calls if debug is disabled
#if DEBUG
#define CDEBUG(...) display.clearDisplay(##__VA_ARGS__)
#define PDEBUG(x, y, str) {\
  display.setCursor(x, y);\
  display.print(str);\
  display.display();\
}
#else
#define PDEBUG(x, y, str) 
#define CDEBUG(...) 
#endif

#define PINFO(x, y, str) {\
  display.setCursor(x, y);\
  display.print(str);\
}
#define UINFO(...) display.partialUpdate(##__VA_ARGS__)

Inkplate display(INKPLATE_1BIT);
const size_t refresh_interval = 10;
size_t refresh_timer = 0;


char ssid[] = "jebediah";   //"privlab";
char pass[] = "1234567890"; //"tangible@privacy6503";
char serverAddress[] = "5.135.157.234";  // server address                          //need
int port = 5000;    
WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);

size_t display_id=0;

enum e_direction {
  RIGHT = 1,
  UP = 2,
  DOWN = 3,
  LEFT = 4  
};

void setup() {
  // put your setup code here, to run once:
  display.begin();
  display.clearDisplay();
  display.display();
  
  display.setRotation(3);
  display.setTextSize(4);
  PINFO(100, 100, "Loading...");
  UINFO();

  Serial.begin(57600);
  PINFO(100, 200, "trying to connect");
  UINFO();
  int i = 0;
  do {
    PINFO(100+i*4, 220, ".");
    UINFO();
    WiFi.begin(ssid, pass);

  } while ( WiFi.waitForConnectResult() != WL_CONNECTED);
    
  PINFO(100, 300, "connected!");
  UINFO();

  PINFO(100, 400, "Done...");
  UINFO();

}

void loop() {

  check_touch_pads();
  
  CDEBUG();
  PDEBUG(100, 100, "Getting...");

  String response = get_from_server(display_id);
  
  PDEBUG(100, 200, "Done!");

  std::vector<String> v_dir;
  std::vector<String> v_uid;
  parse_JSON(response, v_dir, v_uid);

  if (refresh_timer == 0) {
    display.clearDisplay(); // Clear any data that may have been in (software) frame buffer.
    display.display();
    setDisplayOutline();
  } else {
    refresh_timer--;
  }
  
  for ( int i = 0; i<v_dir.size(); i++) {
    size_t dir;
    switch ( v_dir[i][0] ) {
      case 'r':
        dir = e_direction::RIGHT;
        break;
      case 'u':
        dir = e_direction::UP;
        break;
      case 'd':
        dir = e_direction::DOWN;
        break;
      default: // l
        dir = e_direction::LEFT;
        break;
    }
    drawShape(1, i+1, v_uid[i][0], v_uid[i][2]);
    drawShape(2, i+1, v_uid[i][4], v_uid[i][6]);
    drawShape(3, i+1, v_uid[i][8], v_uid[i][10]);
    drawDirection(i+1, dir);
  }
  if (refresh_timer == 0) {
    display.display();
    refresh_timer = refresh_interval;
  } else {
    display.partialUpdate();
  }


}


void check_touch_pads() {
  if( display.readTouchpad(PAD1) ) {
    PDEBUG(100, 100, "TOUCH 1");
    if( display_id > 0 ) {
      display_id--;
      refresh_timer = 0;
    }
  }
  if( display.readTouchpad(PAD2) ) {
    PDEBUG(100, 100, "TOUCH 2");
    display_id = 0;
    refresh_timer = 0;
  }
  if( display.readTouchpad(PAD3) ) {
    PDEBUG(100, 100, "TOUCH 3");
    if( display_id < 10 ) {
      display_id++;
      refresh_timer = 0;
    }
  }
}

void parse_JSON(const String &response, std::vector<String> &v_dir, std::vector<String> &v_uid) {
  
  JSONVar myArr = JSON.parse(response);
  if (JSON.typeof(myArr) == "undefined") {
    CDEBUG();
    PDEBUG(100, 100, "error parsing");
    return;
  }

  size_t len = myArr.length();
  if (len == 0) {
    CDEBUG();
    PDEBUG(100, 100, "no info");
    return;
  }
  
  CDEBUG();
  
  for (int i = 0; i<len; i++) {
    JSONVar direction_info = myArr[i];
    const char *uid = NULL;
    const char *dir = NULL;
  
    if (direction_info.hasOwnProperty("UID") && direction_info.hasOwnProperty("DIRECT")) {
      uid = (const char *)(direction_info["UID"]);
      dir = (const char *)(direction_info["DIRECT"]);
      v_uid.emplace_back(String(uid));
      v_dir.emplace_back(String(dir));
    }
  
    PDEBUG(100, 100+i*200, uid);
    PDEBUG(100, 200+i*200, dir);

  }

}

String get_from_server(size_t id) {
    String request = "/get_direction?DISPLAY=" + String(id);
    client.get(request);
    int statusCode = client.responseStatusCode();
    String response = client.responseBody();
    CDEBUG();
    PDEBUG(100, 200, String(statusCode));
    
    if (statusCode/100 != 2 ) {
      return "";
    }
    return response;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void drawShape(int o, int p, char s, char c)
{
  int clr = 0;
  if(c == 'B') clr = 1;

  if(s == 'C'){
    drawUserCircle(o,p,clr);
  }
  else if(s == 'T'){
    drawUserTriangle(o,p,clr);
  }
  else if(s == 'S'){
    drawUserSquare(o,p,clr);
  }
  else{
    drawUserDiamond(o,p,clr);
  }

}

void drawUserTriangle(int order, int position, bool color){
  int x_axis, y_axis, x_1, y_1, x_2, y_2, x_3, y_3;
  if(order == 1){
    x_axis = 75;
  }else if(order == 2){
    x_axis = 200;
  }else if(order == 3){
    x_axis = 325;
  }

  y_axis = (position *115) + 50;

  x_1 = x_axis;
  x_2 = x_axis - 50;
  x_3 = x_axis + 50;
  y_1 = y_axis - 50;
  y_2 = y_axis + 50;
  y_3 = y_axis + 50;


  if(color){
    display.fillTriangle(x_1, y_1, x_2, y_2, x_3, y_3, BLACK);
  }else{
    display.drawTriangle(x_1, y_1, x_2, y_2, x_3, y_3, BLACK);
  }
}

//825x1200
void drawDirection(int position, int direction){
  int x_axis_1 = 750, x_axis_2 = 625, x_axis_3 = 500, y_axis;

  y_axis = (position * 115) + 50;


  if(direction == 1){  //right
    drawRight(x_axis_1, y_axis);
    drawRight(x_axis_2, y_axis);
    drawRight(x_axis_3, y_axis);
  }else if(direction == 2){ //up
    drawUp(x_axis_1, y_axis);
    drawUp(x_axis_2, y_axis);
    drawUp(x_axis_3, y_axis);
  }else if(direction == 3){
    drawDown(x_axis_1, y_axis);
    drawDown(x_axis_2, y_axis);
    drawDown(x_axis_3, y_axis);
  }else if(direction == 4){
    drawLeft(x_axis_1, y_axis);
    drawLeft(x_axis_2, y_axis);
    drawLeft(x_axis_3, y_axis);
  }
}

void drawRight(int x, int y){
  display.fillTriangle(x, y-50, x, y+50, x+50, y, BLACK);
  display.fillRect(x-50, y-25, 50, 50, BLACK);
}

void drawUp(int x, int y){
  display.fillTriangle(x, y-50, x-50, y, x+50, y, BLACK);
  display.fillRect(x-25, y, 50, 50, BLACK);
}

void drawDown(int x, int y){
  display.fillTriangle(x, y+50, x-50, y, x+50, y, BLACK);
  display.fillRect(x-25, y-50, 50, 50, BLACK);
}

void drawLeft(int x, int y){
  display.fillTriangle(x, y-50, x, y+50, x-50, y, BLACK);
  display.fillRect(x, y-25, 50, 50, BLACK);
}

void drawUserDiamond(int order, int position, bool color){
  int x_axis, y_axis, x_1, y_1_1, y_2_1, x_2, y_2, x_3, y_3;
  if(order == 1){
    x_axis = 75;
  }else if(order == 2){
    x_axis = 200;
  }else if(order == 3){
    x_axis = 325;
  }

  y_axis = (position *115) + 50;

  x_1 = x_axis;
  x_2 = x_axis - 50;
  x_3 = x_axis + 50;
  
  y_1_1 = y_axis - 50;
  y_2_1 = y_axis + 50;
  y_2 = y_axis;
  y_3 = y_axis;


  if(color){
    display.fillTriangle(x_1, y_1_1, x_2, y_2, x_3, y_3, BLACK);
    display.fillTriangle(x_1, y_2_1, x_2, y_2, x_3, y_3, BLACK);
  }else{
    display.drawTriangle(x_1, y_1_1, x_2, y_2, x_3, y_3, BLACK);
    display.drawTriangle(x_1, y_2_1, x_2, y_2, x_3, y_3, BLACK);
  }
}

void drawUserSquare(int order, int position, bool color){
  int x_axis, y_axis;  

  if(order == 1){
    x_axis = 75;
  }else if(order == 2){
    x_axis = 200;
  }else if(order == 3){
    x_axis = 325;
  }

  y_axis = (position *115) + 50;


  if(color){
    display.fillRect(x_axis - 50, y_axis - 50, 100, 100, BLACK);
  }else{
    display.drawRect(x_axis - 50, y_axis - 50, 100, 100, BLACK);
  }
}


void drawUserCircle(int order, int position, bool color){
  int x_axis;
  int y_axis;

  if(order == 1){
    x_axis = 75;
  }else if(order == 2){
    x_axis = 200;
  }else if(order == 3){
    x_axis = 325;
  }

  y_axis = (position * 115) + 50;

  if(color){
    display.fillCircle(x_axis, y_axis, 50, BLACK);
  }else{
    display.drawCircle(x_axis, y_axis, 50, BLACK);
  }
}





void displayTextID(char* userID, int userPosition){
  int y_axis = 50;
  y_axis += (50 * userPosition);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(20, y_axis);
  display.setTextSize(4);
  display.print(userID);
}


void displayTextDirection(char* direct, int userPosition){
  int y_axis = 50;
  y_axis += (50* userPosition);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(400, y_axis);
  display.setTextSize(4);
  display.print(direct);
}

//825x1200
void setDisplayOutline(){
    display.fillRect(0, 0, 825, 100, BLACK);
    display.setTextColor(WHITE, BLACK);
    display.setTextSize(6);
    display.setCursor(475, 30);
    display.print("DIRECTION");
    display.fillRect(387, 0, 50, 1200, BLACK);
    display.setCursor(75, 30);
    display.print("USER ID (" + String(display_id) +")");
}
