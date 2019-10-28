#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "driver/gpio.h"

#define GPIO_OUTPUT_IO_0    GPIO_NUM_2   // Chan 2 trong gpio.h của kiểu gpio_num_t
#define GPIO_OUTPUT_IO_1    GPIO_NUM_3
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1))


void coreTask( void * pvParameters ){
 
    String taskMessage = "Task running on core ";
    taskMessage = taskMessage + xPortGetCoreID();
 
    while(true){
        
    }
 
}
boolean status_led=true;
void setup() {
  // put your setup code here, to run once:
      Serial.begin(115200);
    /*
    * Cài Output
    */
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE; //disable interrupt  
    io_conf.mode = GPIO_MODE_OUTPUT;       //set as output mode
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL; 
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;//disable pull-down mode  
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;//disable pull-up mode    
    gpio_config(&io_conf);//configure GPIO with the given settings
   
    xTaskCreatePinnedToCore(
                        coreTask,   /* Function to implement the task */
                        "coreTask", /* Name of the task */
                        10000,      /* Stack size in words */
                        NULL,       /* Task input parameter */
                        0,          /* Priority of the task */
                        NULL,       /* Task handle. */
                        1);  /* Core where the task should run */
}

void loop() {
  status_led=!status_led;
  gpio_set_level(GPIO_OUTPUT_IO_0, status_led);
  delay(900);
}
