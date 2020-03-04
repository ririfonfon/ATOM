#include <Arduino.h>

#include <Wire.h>

#include "M5Atom.h"

///////////////////////////////////////PWM setting/////////////////////////////////////////
int freq = 12000;
int resolution = 16;
int ledChannela = 4;
int ledChannelb = 5;
int ledChannelc = 6;
int ledPina = 22;
int ledPinb = 19;
int ledPinc = 23;
uint8_t ledArray[3] = {1, 2, 3}; // three led channels
const boolean invert = false;    // set true if common anode, false if common cathode

float r = 150;
float v = 150;
float b = 255;

int led_r = 255;
int led_v = 255;
int led_b = 255;

///////////////////////////////////////Btn setting/////////////////////////////////////////
uint8_t FSM = 0;

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
      r = 255;
      v = 0;
      b = 0;
      break;
    case 1:
      r = 0;
      v = 255;
      b = 0;
      break;
    case 2:
      r = 0;
      v = 0;
      b = 255;
      break;
    case 3:
      r = 255;
      v = 255;
      b = 0;
      break;
    case 4:
      r = 255;
      v = 0;
      b = 255;
      break;
    case 5:
      r = 0;
      v = 255;
      b = 255;
      break;
    case 6:
      r = 255;
      v = 255;
      b = 255;
      break;

    }

    FSM++;
    if (FSM >= 7)
    {
      FSM = 0;
    }
  }
  pwm_show();
  delay(50);
  M5.update();
}

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