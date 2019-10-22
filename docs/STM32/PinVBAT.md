---
layout: default
title: 
---

Pin VBAT dùng lưu trữ SRAM Dự Phòng và RTC khi STM32 mất điện.
Các biến được lưu trên SRAM Dự Phòng sẽ không bị mất.


Mún dùng SRAM này ta phải khai báo trong stm32.
Khai báo biến nằm trong vùng SRAM để sử dụng và đọc lại giá trị.
```
Enable the PWR clock

RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
Enable access to the backup domain

PWR_BackupAccessCmd(ENABLE);
Enable backup SRAM Clock

RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_BKPSRAM, ENABLE);
Enable the Backup SRAM low power Regulator to retain it's content in VBAT mode

PWR_BackupRegulatorCmd(ENABLE);

các hàm này trong STM32F4xx_DSP_StdPeriph_Lib
```



<pre class='brush: cpp'>
Với địa chỉ 0x40024000 là một ô nhớ SRAM, mỗi loại stm sẽ có vùng nhớ khác nhau.
#define VAR_LOC ((volatile uint8_t *)(0x40024000))
volatile uint8_t *pVar = VAR_LOC;
*pVar = 5;
</pre>