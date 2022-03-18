#ifndef ARDUINO_INKPLATE10
#error "Wrong board selection for this example, please select Inkplate 10 in the boards menu."
#endif

#include "Inkplate.h"
Inkplate display(INKPLATE_1BIT);

#define DELAY_MS 5000
// Delay in milliseconds between screen refresh. Refreshing e-paper screens more often than 5s is not
// recommended
// Want to refresh faster? Use partial update! Find example in "3-Inkplate-basic_partial_update"

void setup()
{
    display.begin();        // Init library (you should call this function ONLY ONCE)
    display.setRotation(3);
    display.clearDisplay();
    setDisplayOutline();
    
    drawUserSquare(1,1,true);
    drawUserDiamond(2,1,false);
    drawUserTriangle(3,1,true);
    drawUserDiamond(1,2,false);
    drawUserDiamond(2,2,true);
    drawUserDiamond(3,2,false);    
    
    drawUserTriangle(1,3,true);
    drawUserTriangle(1,4,false);
    drawUserTriangle(1,5,true);
    drawUserTriangle(1,6,false);
    drawUserTriangle(1,7,true);
    drawUserTriangle(1,8,false);
    drawUserTriangle(1,9,true);
    drawDirection(1,1);
    drawDirection(2,2);
    drawDirection(3,3);
    drawDirection(4,4);
    
    drawDirection(1,1);

    display.display();
    delay(5000);
}

void loop()
{

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
