---
layout: default
title: 
---

Mutex cũng gần giống binary semaphore. 
Các tác vụ sẽ dùng 1 khóa, khi tác vụ này chiếm khóa thì các tác vụ khác sẽ chờ cho tác vụ chiếm khóa thục hiện nhả khóa.
Khác với binary semaphore là Mutex khi lấy khóa thì phải giải phóng khóa.
```

SemaphoreHandle_t xMutex;
void setup() {
  Serial.begin(112500);
  /* create Mutex */
  xMutex = xSemaphoreCreateMutex();
  
  xTaskCreate(
      lowPriorityTask,           /* Task function. */
      "lowPriorityTask",        /* name of task. */
      1000,                    /* Stack size of task */
      NULL,                     /* parameter of the task */
      1,                        /* priority of the task */
      NULL);                    /* Task handle to keep track of created task */
  delay(500);
  /* let lowPriorityTask run first then create highPriorityTask */
  xTaskCreate(
      highPriorityTask,           /* Task function. */
      "highPriorityTask",        /* name of task. */
      1000,                    /* Stack size of task */
      NULL,                     /* parameter of the task */
      4,                        /* priority of the task */
      NULL);                    /* Task handle to keep track of created task */
}

void loop() {

}
void lowPriorityTask( void * parameter )
{
  Serial.println((char *)parameter);
  for(;;){
    Serial.println("lowPriorityTask gains key");
    xSemaphoreTake( xMutex, portMAX_DELAY );
    /* even low priority task delay high priority 
    still in Block state */
    delay(2000);
    Serial.println("lowPriorityTask releases key");
    xSemaphoreGive( xMutex );
  }
  vTaskDelete( NULL );
}

void highPriorityTask( void * parameter )
{
  Serial.println((char *)parameter);
  for(;;){
    Serial.println("highPriorityTask gains key");
    /* highPriorityTask wait until lowPriorityTask release key */
    xSemaphoreTake( xMutex, portMAX_DELAY );
    Serial.println("highPriorityTask is running");
    Serial.println("highPriorityTask releases key");
    xSemaphoreGive( xMutex );
    /* delay so that lowPriorityTask has chance to run */
    delay(1000);
  }
  vTaskDelete( NULL );
}

```