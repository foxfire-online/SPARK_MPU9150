#include "FOXFIRE_MPU9150.h"

//http://pansenti.wordpress.com/2013/03/26/pansentis-invensense-mpu-9150-software-for-arduino-is-now-on-github/
//Thank you to pansenti for setup code.
//I will documented this one later.
void MPU9150_setupCompass(int addrCompass, int addrMotion){
  MPU9150_writeSensor(addrCompass, 0x0A, 0x00); //PowerDownMode
  MPU9150_writeSensor(addrCompass, 0x0A, 0x0F); //SelfTest
  MPU9150_writeSensor(addrCompass, 0x0A, 0x00); //PowerDownMode

  MPU9150_writeSensor(addrMotion, 0x24, 0x40); //Wait for Data at Slave0
  MPU9150_writeSensor(addrMotion, 0x25, 0x8C); //Set i2c address at slave0 at 0x0C
  MPU9150_writeSensor(addrMotion, 0x26, 0x02); //Set where reading at slave 0 starts
  MPU9150_writeSensor(addrMotion, 0x27, 0x88); //set offset at start reading and enable
  MPU9150_writeSensor(addrMotion, 0x28, 0x0C); //set i2c address at slv1 at 0x0C
  MPU9150_writeSensor(addrMotion, 0x29, 0x0A); //Set where reading at slave 1 starts
  MPU9150_writeSensor(addrMotion, 0x2A, 0x81); //Enable at set length to 1
  MPU9150_writeSensor(addrMotion, 0x64, 0x01); //overvride register
  MPU9150_writeSensor(addrMotion, 0x67, 0x03); //set delay rate
  MPU9150_writeSensor(addrMotion, 0x01, 0x80);

  MPU9150_writeSensor(addrMotion, 0x34, 0x04); //set i2c slv4 delay
  MPU9150_writeSensor(addrMotion, 0x64, 0x00); //override register
  MPU9150_writeSensor(addrMotion, 0x6A, 0x00); //clear usr setting
  MPU9150_writeSensor(addrMotion, 0x64, 0x01); //override register
  MPU9150_writeSensor(addrMotion, 0x6A, 0x20); //enable master i2c mode
  MPU9150_writeSensor(addrMotion, 0x34, 0x13); //disable slv4
}

////////////////////////////////////////////////////////////
///////// I2C functions to get all values easier ///////////
////////////////////////////////////////////////////////////

int MPU9150_readSensor(int addrI2C, int addrL, int addrH){
  Wire.beginTransmission(addrI2C);
  Wire.write(addrL);
  Wire.endTransmission(false);

  Wire.requestFrom(addrI2C, 1, true);
  byte L = Wire.read();

  Wire.beginTransmission(addrI2C);
  Wire.write(addrH);
  Wire.endTransmission(false);

  Wire.requestFrom(addrI2C, 1, true);
  byte H = Wire.read();

  return (int16_t)((H<<8)+L);
}

int MPU9150_readSensor(int addrI2C, int addr){
  Wire.beginTransmission(addrI2C);
  Wire.write(addr);
  Wire.endTransmission(false);

  Wire.requestFrom(addrI2C, 1, true);
  return Wire.read();
}

int MPU9150_writeSensor(int addrI2C, int addr, int data){
  Wire.beginTransmission(addrI2C);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission(true);

  return 1;
}
