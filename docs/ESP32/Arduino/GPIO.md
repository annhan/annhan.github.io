---
layout: default
title: 
---
Chip ESP32 có 40 pad chức năng vật lý. Một số pad không được dùng hoặc không có chân tương ứng trên chip (tham khảo datasheet). Mỗi pad có thể dùng như một chân I/O hoặc có thể kết nối với một chân tín hiệu khác của ESP32.<br>

Note: GPIO-11 thường dùng cho SPI flash.<br>
GPIO-34-39 chỉ có thể được set là kiểu chân input và không thể dùng phần mềm để pull-up và pull-down.<br>
Ngoài ra còn hỗ trợ riêng "RTC GPIO", có chức năng khi các chân GPIO định tuyến đến hệ thống con "RTC" low-power và analog. Những pin chức năng này có thể sử dụng khi sleep, khi Ultra Low Power co-processor đang chạy, hay khi các chức năng analog như ADC, DAC, v.v đang dùng.<br>

```
/* Button Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_GPIO 23
#define BTN_GPIO 18

void button_task(void *pvParameter)
{
    /* Configure the IOMUX register for pad LED_GPIO, BTN_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_pad_select_gpio(LED_GPIO);
    gpio_pad_select_gpio(BTN_GPIO);

    /* Set the GPIO as a push/pull output */
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    gpio_set_direction(BTN_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BTN_GPIO, GPIO_PULLUP_ONLY);

    while(1) {
        if (gpio_get_level(BTN_GPIO) == 0) {
                gpio_set_level(LED_GPIO, 0);
        }
        else
                gpio_set_level(LED_GPIO, 1);
    }
}

void app_main()
{
    xTaskCreate(&button_task, "button_task", 512, NULL, 5, NULL);
}
```