---
layout: default
title: 
---

Arduino ESP32 được build trên nền FreeRTOS và hàm mainloop là một looptask.<br>
Để phát huy được tính đa nhiệm và bộ nhớ RTOS thì ta cần tạo nhiệm vụ (task)<br>
VD: Mainloop là 1 task và additionalTask là một task.<br>
  xTaskCreate(
      additionalTask,           /* Task function. */
      "additional Task",        /* name of task. */
      10000,                    /* Stack size of task */
      NULL,                     /* parameter of the task */
      1,                        /* priority of the task */
      nhan_chay);                    /* Task handle to keep track of created task */
}
phần nhân chạy ta có thể chỉnh là 1. Vì mặt định ESP32 chạy trên nhân số 0 và để NULL thì task sẽ thực hiện trên nhân 0.<br>
ESP32 có 2 nhân nên có thể chạy song song.<br>
```
void setup() {

  Serial.begin(112500);
  /* we create a new task here */
  xTaskCreate(
      additionalTask,           /* Task function. */
      "additional Task",        /* name of task. */
      10000,                    /* Stack size of task */
      NULL,                     /* parameter of the task */
      1,                        /* priority of the task */
      NULL);                    /* Task handle to keep track of created task */
}

/* the forever loop() function is invoked by Arduino ESP32 loopTask */
void loop() {
  Serial.println("this is Arduino Task");
  delay(1000);
}
/* this function will be invoked when additionalTask was created */
void additionalTask( void * parameter )
{
  /* loop forever */
  for(;;){
    Serial.println("this is additional Task");
    delay(1000);
  }
  /* delete a task when finish, 
  this will never happen because this is infinity loop */
  vTaskDelete( NULL );
}
```