 	
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
 
MPU6050 mpu;
 
int16_t ax, ay, az;
int16_t gx, gy, gz;
 
int fval;
int bval;
int yprevVal;
int lval;
int rval;
int xprevVal;
//int yprevVal;
 
void setup()
{
    Wire.begin();
    Serial.begin(38400);
 
    Serial.println("Initialize MPU");
    mpu.initialize();
    Serial.println(mpu.testConnection() ? "Connected" : "Connection failed");

}
 
void loop()
{
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
 
    lval = map(ay, -17000, 0, -255, 100);
    if (lval != yprevVal && ay < -5000 && ax < 8000 && ax > -8000 )
    {   
      //yval = yval+100;
        Serial.println("Robot Moves LEFT");
        Serial.println(lval);
        yprevVal =lval;
    }
     else
     {
   //  Serial.println("ROBOT Stop y =0~90");
     }
    rval = map(ay, 0, 17000, -100, 255);
    if (rval != yprevVal && ay > 5000 && ax < 8000 && ax > -8000)
    {
      //yval = yval -100;
        Serial.println("Robot Moves RIGHT");
        Serial.println(rval);
        yprevVal = rval;
    }
     else
     {
   //  Serial.println("ROBOT Stop y=90~180");
     }
    delay(50);
 
    fval = map(ax, -17000, 0, -255, 100);
    if (fval != xprevVal && ax < -5000 && ay < 8000 && ay > -8000)
    {
        Serial.println("Robot Moves FORWARD");
        Serial.println(fval);
        xprevVal = fval;
    }
      else
     {
  //   Serial.println("ROBOT Stop x =0~90");
     }
    bval = map(ax, 0, 17000, -100, 255);
    if (bval != xprevVal && ax > 5000 && ay < 8000 && ay > -8000)
    {
        Serial.println("Robot Moves BACK");
        Serial.println(bval);
        xprevVal = bval;
    }
     else
     {
  //   Serial.println("ROBOT Stop x =90~180");
     } 
    delay(50);
}
