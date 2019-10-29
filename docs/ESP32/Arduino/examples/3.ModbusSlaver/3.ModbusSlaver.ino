
#include "ModbusRTU.h"

#define REGN 10
#define COIL 5
#define SLAVE_ID 1
// Khai bao PWM 
const int freq = 5000; //tần số
const int ledChannel = 1; //ESP 32 có 16 kênh PWM rieng biệt
const int resolution = 16; // độ phân giải 16 bit 0-65535

ModbusRTU mb;
uint16_t data=0;
void setup() {
  //pinMode(2, OUTPUT);
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(2, ledChannel);
  Serial.begin(9600, SERIAL_8N1);
  mb.begin(&Serial);
  mb.slave(SLAVE_ID);
  mb.addHreg(REGN,300,2);
  mb.addCoil(COIL, 1, 10);
  mb.Hreg(REGN, 100);
}

void loop() {
  mb.task();
  yield();
  data += 60;
  mb.Hreg(REGN, data);
 // digitalWrite(2,mb.Coil(COIL));
 ledcWrite(ledChannel, mb.Hreg(REGN+1));
// analogWrite(2,);
}
