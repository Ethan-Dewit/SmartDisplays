/*a example of  how we wll pares json files 
fetched from our server!
*/
#include <Arduino_JSON.h>
#include "Inkplate.h"
Inkplate display(INKPLATE_1BIT);
#define DELAY_MS 5000

//an example of how our json will be sent
const char input[] = "{\"direction\":1,\"sc1\":40,\"sc2\":11,\"sc3\":20}";


void setup() {
  Serial.begin(9600);
  while (!Serial);
 
 
  int d = getDir(); 
  int sym1 = getSym1();
  int sym2 = getSym2();
  int sym3 = getSym3();

  int s1 = sym1/10;
  int s2 = sym2/10;
  int s3 = sym3/10;
  int c1 = sym1%10;
  int c2 = sym2%10;
  int c3 = sym3%10;

  display.begin();        
  display.setRotation(3);
  display.clearDisplay();
  setDisplayOutline();

  if(s1 = 0){
    drawUserCircle(1,1,c1);
  }
  else if(s1 = 1){
    drawUserTriangle(1,1,c1);
  }
  else if(s1 = 2){
    drawUserSquare(1,1,c1);
  }
  else{
    drawUserDiamond(1,1,c1);
  }


  if(s2 = 0){
    drawUserCircle(2,1,c2);
  }
  else if(s2 = 1){
    drawUserTriangle(2,1,c2);
  }
  else if(s2 = 2){
    drawUserSquare(2,1,c2);
  }
  else{
    drawUserDiamond(2,1,c2);
  }


  if(s3 = 0){
    drawUserCircle(3,1,c3);
  }
  else if(s3 = 1){
    drawUserTriangle(3,1,c3);
  }
  else if(s3 = 2){
    drawUserSquare(3,1,c3);
  }
  else{
    drawUserDiamond(3,1,c3);
  }
  
  
  
  
  
  
  drawDirection(1,d);

  display.display();
  delay(5000);

}

void loop() {
}

int getDir()
{
  int d = 0;
  JSONVar myObject = JSON.parse(input);

  if (JSON.typeof(myObject) == "undefined") {
    return d;
  }

  if (myObject.hasOwnProperty("direction")) {
    d = ((int) myObject["direction"]);
  }
  return d;
}


int getSym1()
{
  int sym = 0;
  JSONVar myObject = JSON.parse(input);

  if (JSON.typeof(myObject) == "undefined") {
    return sym;
  }

  if (myObject.hasOwnProperty("sc1")) {
    sym = ((int) myObject["sc1"]);
  }
  return sym;
}

int getSym2()
{
  int sym = 0;
  JSONVar myObject = JSON.parse(input);

  if (JSON.typeof(myObject) == "undefined") {
    return sym;
  }

  if (myObject.hasOwnProperty("sc2")) {
    sym = ((int) myObject["sc2"]);
  }
  return sym;
}

int getSym3()
{
  int sym = 0;
  JSONVar myObject = JSON.parse(input);

  if (JSON.typeof(myObject) == "undefined") {
    return sym;
  }

  if (myObject.hasOwnProperty("sc3")) {
    sym = ((int) myObject["sc3"]);
  }
  return sym;
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
    display.clearDisplay(); // Clear any data that may have been in (software) frame buffer.
    display.fillRect(0, 0, 825, 100, BLACK);
    display.setTextColor(WHITE, BLACK);
    display.setTextSize(6);
    display.setCursor(75, 30);
    display.print("USER ID");
    display.setCursor(475, 30);
    display.print("DIRECTION");
    display.fillRect(387, 0, 50, 1200, BLACK);
}


