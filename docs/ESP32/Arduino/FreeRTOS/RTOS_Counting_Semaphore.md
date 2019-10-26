---
layout: default
title: 
---

Counting Semaphore dùng để lưu trữ nhiều sự kiện Semaphore hơn.
```xCountingSemaphore = xSemaphoreCreateCounting( 10, 0 );``` khai báo biến xCountingSemaphore lưu 10 dữ liệu.
Vd: Chương trình dưới khi nhấn button tạo ra 1 ngắt. Thì ngắt này tạo biến xCountingSemaphore đến 6 lần và task ISRprocessing sẽ blink LED 3 lần theo 6 lần của biến.
```
/* LED pin */
byte ledPin = 14;
/* pin that is attached to interrupt */
byte interruptPin = 12;
/* hold the state of LED when toggling */
volatile byte state = LOW;
SemaphoreHandle_t xCountingSemaphore;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  /* set the interrupt pin as input pullup*/
  pinMode(interruptPin, INPUT_PULLUP);
  /* attach interrupt to the pin
  function blink will be invoked when interrupt occurs
  interrupt occurs whenever the pin rising value */
  attachInterrupt(digitalPinToInterrupt(interruptPin), ISRcallback, RISING);
  /* initialize counting semaphore that can store 10 events */
  xCountingSemaphore = xSemaphoreCreateCounting( 10, 0 );
  /* this task will process the interrupt event 
  which is forwarded by interrupt callback function */
  xTaskCreate(
    ISRprocessing,           /* Task function. */
    "ISRprocessing",        /* name of task. */
    1000,                    /* Stack size of task */
    NULL,                     /* parameter of the task */
    4,                        /* priority of the task */
    NULL);  
}

void loop() {
}

/* interrupt function callback */
void ISRcallback() {
  /* */
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  /* un-block the interrupt processing task now */
  /* each couple is a blinky cycle 
  we bink 3 times then call this 6 times */
  xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );
  xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );
  xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );
  xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );
  xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );
  xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );
}

/* this function will be invoked when additionalTask was created */
void ISRprocessing( void * parameter )
{
  Serial.println((char *)parameter);
  /* loop forever */
  for(;;){
    /* task move to Block state to wait for interrupt event */
    xSemaphoreTake( xCountingSemaphore, portMAX_DELAY );
    Serial.println("ISRprocessing is running");
    /* toggle the LED now */
    state = !state;
    digitalWrite(ledPin, state);
    /* elay here to see LED blinky */
    delay(1000);
  }
  vTaskDelete( NULL );
}
```