#include "Arduino.h"
#include "Inkplate.h"
#include "Fonts/FreeSansBold24pt7b.h"

extern Inkplate display;

String text0_content = "To 5032";
int text0_cursor_x = 304;
int text0_cursor_y = 62;
const GFXfont *text0_font = &FreeSansBold24pt7b;

int circle0_center_x = 400;
int circle0_center_y = 246;
int circle0_fill = -1;
int circle0_radius = 48;
int circle0_color = 0;

int triangle0_a_x = 400;
int triangle0_a_y = 200;
int triangle0_b_x = 440;
int triangle0_b_y = 270;
int triangle0_c_x = 360;
int triangle0_c_y = 270;
int triangle0_fill = -1;
int triangle0_radius = -1;
int triangle0_color = 0;

int triangle1_a_x = 600;
int triangle1_a_y = 380;
int triangle1_b_x = 530;
int triangle1_b_y = 340;
int triangle1_c_x = 530;
int triangle1_c_y = 420;
int triangle1_fill = 1;
int triangle1_radius = -1;
int triangle1_color = 0;

int rect0_a_x = 240;
int rect0_a_y = 360;
int rect0_b_x = 537;
int rect0_b_y = 400;
int rect0_fill = 1;
int rect0_radius = -1;
int rect0_color = 0;

void mainDraw() {
    display.setFont(text0_font);
    display.setTextColor(0, 7);    display.setTextSize(1);    display.setCursor(text0_cursor_x, text0_cursor_y);
    display.print(text0_content);

    if (circle0_fill != -1)
       display.fillCircle(circle0_center_x, circle0_center_y, circle0_radius, circle0_color);
   else
       display.drawCircle(circle0_center_x, circle0_center_y, circle0_radius, circle0_color);

    if (triangle0_fill != -1)
       display.fillTriangle(triangle0_a_x, triangle0_a_y, triangle0_b_x, triangle0_b_y, triangle0_c_x, triangle0_c_y, triangle0_color);
   else
       display.drawTriangle(triangle0_a_x, triangle0_a_y, triangle0_b_x, triangle0_b_y, triangle0_c_x, triangle0_c_y, triangle0_color);

    if (triangle1_fill != -1)
       display.fillTriangle(triangle1_a_x, triangle1_a_y, triangle1_b_x, triangle1_b_y, triangle1_c_x, triangle1_c_y, triangle1_color);
   else
       display.drawTriangle(triangle1_a_x, triangle1_a_y, triangle1_b_x, triangle1_b_y, triangle1_c_x, triangle1_c_y, triangle1_color);

    if (rect0_radius != -1 && rect0_fill != -1)
       display.fillRoundRect(rect0_a_x, rect0_a_y, rect0_b_x - rect0_a_x, rect0_b_y - rect0_a_y, rect0_radius, rect0_color);
   else if (rect0_radius != -1 && rect0_fill == -1)
       display.drawRoundRect(rect0_a_x, rect0_a_y, rect0_b_x - rect0_a_x, rect0_b_y - rect0_a_y, rect0_radius, rect0_color);
   else if (rect0_radius == -1 && rect0_fill != -1)
       display.fillRect(rect0_a_x, rect0_a_y, rect0_b_x - rect0_a_x, rect0_b_y - rect0_a_y, rect0_color);
   else if (rect0_radius == -1 && rect0_fill == -1)
       display.drawRect(rect0_a_x, rect0_a_y, rect0_b_x - rect0_a_x, rect0_b_y - rect0_a_y, rect0_color);

}
