#include "driver/gpio.h"

#define GPIO_OUTPUT_IO_0    GPIO_NUM_2   // Chan 2 trong gpio.h của kiểu gpio_num_t
#define GPIO_OUTPUT_IO_1    GPIO_NUM_3
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1))
#define GPIO_INPUT_IO_0     GPIO_NUM_4
#define GPIO_INPUT_IO_1     GPIO_NUM_5
#define GPIO_INPUT_PIN_SEL  ((1<<GPIO_INPUT_IO_0) | (1<<GPIO_INPUT_IO_1))
#define ESP_INTR_FLAG_DEFAULT 0
static xQueueHandle gpio_evt_queue = NULL;


static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}


void coreTask( void * pvParameters ){
    uint32_t io_num;
    while(true){
                if(xQueueReceive(gpio_evt_queue, &io_num, 100)) { //100 chờ dữ liệu 100ms
                 
                  printf("GPIO[%d] intr, val: %d\n", io_num, gpio_get_level((gpio_num_t)io_num)); // io_num chỉ trả về số nên phải ép kiểu dữ liệu
               printf("GPIO[%d]\n", io_num);
                }
                delay(500);
                printf("NO WAIT\n");
    }
 
}
boolean status_led=true;
void setup() {
  // put your setup code here, to run once:
      Serial.begin(115200);
    /*
    * Cài Output
    */
   // gpio_set_direction(GPIO_OUTPUT_IO_1, GPIO_MODE_OUTPUT);
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE; //disable interrupt  
    io_conf.mode = GPIO_MODE_OUTPUT;       //set as output mode
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL; 
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;//disable pull-down mode  
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;//disable pull-up mode    
    gpio_config(&io_conf);//configure GPIO with the given settings
    /*
    * Cài INPUT
    */
    io_conf.intr_type = GPIO_INTR_POSEDGE; //enable interrip
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    gpio_config(&io_conf);
    gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_INTR_ANYEDGE); //Thay đổi kiểu ngắt cho 1 chân
    gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void*) GPIO_INPUT_IO_0);//hook isr handler for specific gpio pin
    gpio_isr_handler_add(GPIO_INPUT_IO_1, gpio_isr_handler, (void*) GPIO_INPUT_IO_1);//hook isr handler for specific gpio pin  
    gpio_isr_handler_remove(GPIO_INPUT_IO_0); //Xóa ngắt IO 0
    gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void*) GPIO_INPUT_IO_0); //Bật ngắt


    
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
