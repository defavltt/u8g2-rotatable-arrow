#include <Wire.h>
#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

float degrees;

void setup() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_7x13B_tf);
}

void loop() {
  degrees++;
  if(degrees > 360) {
    degrees = 0;
  }

  delay(10);

  u8g2.clearBuffer();

  int16_t sine1 = sin(deg2rad(degrees)) * 31;
  int16_t sine2 = cos(deg2rad(degrees)) * 31;

  u8g2.drawLine(63,31,63 + sine1,31 + sine2);

  arrow(63 + sine1, 31 + sine2, degrees);

  u8g2.setCursor(80, 9);
  u8g2.print(degrees);

  u8g2.sendBuffer();

}

void arrow(uint16_t x, uint16_t y, uint16_t deg) {
  #define inner_radius 8
  #define outer_radius 16
  
  deg-=90; //degree offset
  
  int16_t a_sin = sin(5.7595 + deg2rad(deg)) * inner_radius;
  int16_t a_cos = cos(5.7595 + deg2rad(deg)) * inner_radius;

  int16_t b_sin = sin(1.5707 + deg2rad(deg)) * outer_radius;
  int16_t b_cos = cos(1.5707 + deg2rad(deg)) * outer_radius;

  int16_t c_sin = sin(3.6651 + deg2rad(deg)) * inner_radius;
  int16_t c_cos = cos(3.6651 + deg2rad(deg)) * inner_radius;

//  /*non-inverted*/
//  u8g2.drawLine(x,y,x+a_sin,y+a_cos);
//  u8g2.drawLine(x+a_sin,y+a_cos,x+b_sin,y+b_cos);
//  u8g2.drawLine(x+b_sin,y+b_cos,x+c_sin,y+c_cos);
//  u8g2.drawLine(x+c_sin,y+c_cos,x,y);

//  /*inverted*/
//  u8g2.drawLine(x,y,x+a_cos,y+a_sin);
//  u8g2.drawLine(x+a_cos,y+a_sin,x+b_cos,y+b_sin);
//  u8g2.drawLine(x+b_cos,y+b_sin,x+c_cos,y+c_sin);
//  u8g2.drawLine(x+c_cos,y+c_sin,x,y);

  /*non-inverted & limited*/
  u8g2.drawLine(x,y,cap(x+a_sin),cap(y+a_cos));
  u8g2.drawLine(cap(x+a_sin),cap(y+a_cos),cap(x+b_sin),cap(y+b_cos));
  u8g2.drawLine(cap(x+b_sin),cap(y+b_cos),cap(x+c_sin),cap(y+c_cos));
  u8g2.drawLine(cap(x+c_sin),cap(y+c_cos),x,y);

//  /*inverted & limited*/
//  u8g2.drawLine(x,y,cap(x+a_cos),cap(y+a_sin));
//  u8g2.drawLine(cap(x+a_cos),cap(y+a_sin),cap(x+b_cos),cap(y+b_sin));
//  u8g2.drawLine(cap(x+b_cos),cap(y+b_sin),cap(x+c_cos),cap(y+c_sin));
//  u8g2.drawLine(cap(x+c_cos),cap(y+c_sin),x,y);
}

float calc_degrees(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
  return atan2(y2 - y1, x2 - x1) * 180 / PI;
}

float deg2rad(float deg) {
  return deg * (PI/180);
}

uint16_t cap(int16_t input) {
  if(input < 0) {
    input = 0;
  }
  return input;
}
