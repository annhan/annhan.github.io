---
layout: default
title: 
---

Chương trình khai báo 1 task.

BaseType_t xTaskCreate( TaskFunction_t pvTaskCode,
                        const char * const pcName,
                        uint16_t usStackDepth,
                        void *pvParameters,
                        UBaseType_t uxPriority,
                        TaskHandle_t *pxCreatedTask )
						
void *pvParameters để truyền dữ liệu vào task.
VD:
Chương trình tạo task sẽ truyền dữ liệu vào task1param.
trong task ta chỉ print datan dữ liệu truyền vào.
```
void setup() {

  Serial.begin(112500);
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
    Serial.println("task1 is running");
    delay(1000);
  }
  /* delete a task when finish, 
  this will never happen because this is infinity loop */
  vTaskDelete( NULL );
}
```
						