#include <Arduino.h>
#include "M5Atom.h"
#include "image.h"

/* this Example only for M5Atom Matrix */

extern const unsigned char AtomImageData[375 + 2];
extern const unsigned char image_Komplex[1307];
extern const unsigned char image_carre[1202];

float accX = 0, accY = 0, accZ = 0;
float gyroX = 0, gyroY = 0, gyroZ = 0;
int posX = 12, posY = 12, posZ = 0;
float temp = 0;
bool IMU6886Flag = false;
uint8_t FSM = 0;

void setup()
{
  M5.begin(true, false, true);
  if (M5.IMU.Init() != 0)
    IMU6886Flag = false;
  else
    IMU6886Flag = true;
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
        M5.dis.animation((uint8_t *)AtomImageData, 100, LED_Display::kMoveLeft, 2500);
        break;
      case 1:
        M5.dis.animation((uint8_t *)image_Komplex, 100, LED_Display::kMoveLeft, 2500);
        break;
      case 2:
        // M5.dis.animation((uint8_t *)image_carre, 100, LED_Display::kStatic, 1);
        // if (IMU6886Flag == true)
        // {
        //   M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
        //   M5.IMU.getAccelData(&accX, &accY, &accZ);
        //   M5.IMU.getTempData(&temp);

        //   Serial.printf("%.2f,%.2f,%.2f o/s \r\n", gyroX, gyroY, gyroZ);
        //   Serial.printf("%.2f,%.2f,%.2f mg\r\n", accX * 1000, accY * 1000, accZ * 1000);
        //   Serial.printf("Temperature : %.2f C \r\n", temp);
        // }
        // M5.dis.displaybuff((uint8_t *)image_carre, gyroX, gyroY);
        break;

      default:
        break;
      }
      FSM++;
      if (FSM >= 3)
      {
        FSM = 0;
      }
    }
  }
  delay(50);
  if (FSM == 2)
  {
    if (IMU6886Flag == true)
    {
      M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
      // Serial.printf("%.2f,%.2f,%.2f o/s \r\n", gyroX, gyroY, gyroZ);
      if (gyroY < -6)
        posX = posX - 1;
      if (gyroY > 6)
        posX = posX + 1;
      if (gyroX < -6)
        posY = posY - 1;
      if (gyroX > 6)
        posY = posY + 1;
    }
    M5.dis.displaybuff((uint8_t *)image_carre, posX, posY);
  }

  M5.update();
}
