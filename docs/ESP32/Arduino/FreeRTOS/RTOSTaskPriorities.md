---
layout: default
title: 
---
Mức độ ưu tiên của các task. Khi task có mức độ ưu tiên lớn hơn sẽ chiếm hết quỹ thời gian thực hiện của task có mức độ ưu tiên thấp hơn.
<br>
```
void setup() {

  Serial.begin(112500);
  char task1Param[12] = "taskParam";
  /* we create a new task here */
  xTaskCreate(
      task1,           /* Task function. */
      "task1",        /* name of task. */
      10000,                    /* Stack size of task */
      (void *)task1Param,                     /* parameter of the task */
      1,                        /* priority of the task */
      NULL);                    /* Task handle to keep track of created task */
  /* let task1 run first then create task2 */
  xTaskCreate(
      task2,           /* Task function. */
      "task2",        /* name of task. */
      10000,                    /* Stack size of task */
      (void *)task1Param,                     /* parameter of the task */
      4,                        /* priority of the task */
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
    Serial.println("task1 is ending");
  }
  /* delete a task when finish, 
  this will never happen because this is infinity loop */
  vTaskDelete( NULL );
}

/* this function will be invoked when additionalTask was created */
void task2( void * parameter )
{
  Serial.println((char *)parameter);
  /* loop forever */
  for(;;){
    Serial.println("task2 is running");
    Serial.println("task2 is ending");
  }
  /* delete a task when finish, 
  this will never happen because this is infinity loop */
  vTaskDelete( NULL );
}
```
Ví dụ trên kết quả in ra là hầu hết của Task 2
