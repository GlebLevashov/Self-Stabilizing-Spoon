#include "Wire.h"
#include "I2Cdev.h"
#include <MPU6050_light.h>
#include <Servo.h>

int ax, ay, az;
Servo sx, sy;

MPU6050 mpu(Wire);
unsigned long timer = 0;


void setup() {

  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
     Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif
  Serial.begin(38400);
  Serial.print("Starting Connection\n");

  Wire.begin();
  byte status = mpu.begin();
  //Serial.prin
  Serial.println("MPU6050 status: ");
  Serial.println(status);
  while (status != 0) { } // stop everything if could not connect to MPU6050
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(10);
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");

  sx.attach(3);
  sy.attach(5);
  sx.write(90);
  sy.write(90);

}

void loop() {
  mpu.update();

  ax = mpu.getAngleX();
  ay = mpu.getAngleY();
  az = mpu.getAngleZ();
  if ((millis() - timer) > 10) { // print data every 10ms
    Serial.print("X : ");
    Serial.print(ax);
    Serial.print("\tY : ");
    Serial.print(ay);
    Serial.print("\tZ : ");
    Serial.println(az);
    timer = millis();
   }
  sx.write(90 - ay);
  sy.write(90 + az);  
}
