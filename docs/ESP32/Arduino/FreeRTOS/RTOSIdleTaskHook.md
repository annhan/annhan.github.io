---
layout: default
title: 
---

Idle Task Hook Function là 1 task có mức độ ưu tiên thấp nhất (0).<br>
ta có thể dùng:<br>
-Làm một số việc nền<br>
-Đo thời gian CPU rảnh<br>
- Đặt mức năng lượng thấp khi không làm gì.<br>
Để sử dụng task này ta cần chèn<br>
"bool ```vApplicationIdleHook( void )```  và gọi ```esp_register_freertos_idle_hook(vApplicationIdleHook)```
<br>
VD:<br>

```
#include "esp_freertos_hooks.h"
int counter = 0;

void setup() {

  Serial.begin(112500);
  esp_register_freertos_idle_hook(vApplicationIdleHook);
  char task1Param[12] = "task1Param";
  /* we create a new task here */
  xTaskCreate(
      task1,           /* Task function. */
      "task1",        /* name of task. */
      10000,                    /* Stack size of task */
      (void *)task1Param,                     /* parameter of the task */
      1,                        /* priority of the task */
      NULL);                    /* Task handle to keep track of created task */
}

/* the forever loop() function is invoked by Arduino ESP32 loopTask */
void loop() {

}
/* this function will be invoked when additionalTask was created */
void task1( void * parameter )
{
  Serial.println((char *)parameter);
  /* loop forever */
  for(;;){
    Serial.print("task1 is running and counter : ");
    Serial.println(counter);
    if(counter > 30000)
    {
      counter = 0;  
    }
    /* block this task so that Idle task has chance to run */
    delay(10);
  }
  /* delete a task when finish, 
  this will never happen because this is infinity loop */
  vTaskDelete( NULL );
}

/* define task hook function */
bool vApplicationIdleHook(void)
{
  counter++;
}
```