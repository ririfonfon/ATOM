#include <Arduino.h>

#include <Wire.h>

#include "M5Atom.h"

///////////////////////////////////////PWM setting/////////////////////////////////////////
int freq = 12000;
int resolution = 16;
int ledChannela = 4;
int ledChannelb = 5;
int ledChannelc = 6;
int ledPina = 19;
int ledPinb = 22;
int ledPinc = 23;
const boolean invert = false;    // set true if common anode, false if common cathode

float r = 250;
float v = 250;
float b = 250;

int led_r = 255;
int led_v = 255;
int led_b = 255;

///////////////////////////////////////Btn setting/////////////////////////////////////////
uint8_t FSM = 0;

void pwm_init()
{
  /////////////////////////////////////////////////PWM setup
  ledcAttachPin(ledPina, ledChannela);
  ledcAttachPin(ledPinb, ledChannelb);
  ledcAttachPin(ledPinc, ledChannelc);
  ledcSetup(ledChannela, freq, resolution);
  ledcSetup(ledChannelb, freq, resolution);
  ledcSetup(ledChannelc, freq, resolution);
}

void pwm_show()
{
  led_r = ((r * r) * 1.007852);
  led_v = ((v * v) * 1.007852);
  led_b = ((b * b) * 1.007852);
  ledcWrite(ledChannela, led_r);
  ledcWrite(ledChannelb, led_v);
  ledcWrite(ledChannelc, led_b);
} //leds_show

void setup()
{
  M5.begin(true, false, true);
  delay(50);

  pwm_init();
  pwm_show();
}

void loop()
{
  if (M5.Btn.wasPressed())
  {

    switch (FSM)
    {
    case 0:
      r = 0;
      v = 255;
      b = 255;
      M5.dis.drawpix(0, 0xf00000);
      break;
    case 1:
      r = 255;
      v = 0;
      b = 255;
      M5.dis.drawpix(0, 0x00f000);
      break;
    case 2:
      r = 255;
      v = 255;
      b = 0;
      M5.dis.drawpix(0, 0x0000f0);
      break;
    case 3:
      r = 0;
      v = 0;
      b = 255;
      M5.dis.drawpix(0, 0xf0f000);
      break;
    case 4:
      r = 0;
      v = 255;
      b = 0;
      M5.dis.drawpix(0, 0xf000f0);
      break;
    case 5:
      r = 255;
      v = 0;
      b = 0;
      M5.dis.drawpix(0, 0x00f0f0);
      break;
    case 6:
      r = 0;
      v = 150;
      b = 0;
      M5.dis.drawpix(0, 0xf0f0f0);
      break;
    case 7:
      r = 255;
      v = 255;
      b = 255;
      M5.dis.drawpix(0, 0x000000);
      break;
    }

    FSM++;
    if (FSM >= 8)
    {
      FSM = 0;
    }
  }
  pwm_show();
  delay(50);
  M5.update();
}
