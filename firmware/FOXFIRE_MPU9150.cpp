#include "FOXFIRE_MPU9150.h"

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
