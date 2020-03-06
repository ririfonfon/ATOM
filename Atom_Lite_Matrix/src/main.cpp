#include <Arduino.h>
#include "M5Atom.h"
#include "image.h"

/* this Example only for M5Atom Matrix */

extern const unsigned char AtomImageData[375 + 2];
extern const unsigned char image_Komplex[1307];
bool IMU6886Flag = false;
uint8_t FSM = 0;

void setup()
{
  M5.begin(true, false, true);
  delay(1000);
}

void loop()
{
  {
    if (M5.Btn.wasPressed())
    {

      switch (FSM)
      {
      case 0:
        M5.dis.animation((uint8_t *)AtomImageData, 100, LED_Display::kMoveLeft, 250);
        break;
      case 1:
        M5.dis.animation((uint8_t *)image_Komplex, 100, LED_Display::kMoveLeft, 250);
        break;
      default:
        break;
      }
      FSM++;
      if (FSM >= 2)
      {
        FSM = 0;
      }
    }
  }
  delay(50);

  M5.update();
}
