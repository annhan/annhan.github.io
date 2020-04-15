---
layout: default
title: 
---
Common API <br>
Add [multiple] regs<br>
```
bool addHreg(uint16_t offset, uint16_t value = 0, uint16_t numregs = 1);
bool addCoil(uint16_t offset, bool value = false, uint16_t numregs = 1);
bool addIsts(uint16_t offset, bool value = false, uint16_t numregs = 1);
bool addIreg(uint16_t offset, uint16_t value = 0, uint16_t nemregs = 1);
```
Write local reg
```
bool Hreg(uint16_t offset, uint16_t value);
bool Coil(uint16_t offset, bool value);
bool Ists(uint16_t offset, bool value);
bool Ireg(uint16_t offset, uint16_t value);
```
Read local reg
```
uint16_t Hreg(uint16_t offset);
bool Coil(uint16_t offset);
bool Ists(uint16_t offset);
uint16_t Ireg(uint16_t offset);
```
Remove reg
```
bool removeHreg(uint16_t offset, uint16_t numregs = 1);
bool removeCoil(uint16_t offset, uint16_t numregs = 1);
bool removeIsts(uint16_t offset, uint16_t numregs = 1);
bool removeIreg(uint16_t offset, uint16_t numregs = 1);
```
void task();
Processing routine. Should be periodically called form loop().

Modbus RTU Specific API
bool begin(SoftwareSerial* port, int16_t txPin=-1); // For ESP8266 only
bool begin(HardwareSerial* port, int16_t txPin=-1);
Assing Serial port. txPin controls transmit enable for MAX-485.

void master();
void slave(uint8_t slaveId);
Select and initialize master or slave mode to work. Switching between modes is not supported. Call is not returning error in this case but behaviour is unpredictible.

uint8_t slave();
Slave mode. Returns configured slave id. Master mode. Returns slave id for active request or 0 if no request in-progress.

```