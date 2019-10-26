---
layout: default
title: 
---
Task handle là thay đổi mức độ ưu tiên hoặc delete task.

VD: Cho task 1 chạy 20 lần rồi thay đổi mức độ ưu tiên để task 1 thực hiên
```
/* variables to hold instances of tasks*/
TaskHandle_t t1 = NULL;
TaskHandle_t t2 = NULL;
int count = 0;

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
      &t1);                    /* Task handle to keep track of created task */
  /* let task1 run first then create task2 */
  xTaskCreate(
      task2,           /* Task function. */
      "task2",        /* name of task. */
      10000,                    /* Stack size of task */
      (void *)task1Param,                     /* parameter of the task */
      4,                        /* priority of the task */
      &t2);                    /* Task handle to keep track of created task */
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
    count++;
    /* if count is 20 then we swap the priority of 2 tasks */
    if(count == 20){
      vTaskPrioritySet( t1, 4 );
      vTaskPrioritySet( t2, 1 );
    }
    Serial.println("task2 is running");
    Serial.println("task2 is ending");
  }
  /* delete a task when finish, 
  this will never happen because this is infinity loop */
  vTaskDelete( NULL );
}
```