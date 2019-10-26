/*
 * https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/uart.html#uart-api-setting-communication-pins
 */
#include "driver/uart.h"
 
#define UART_SO UART_NUM_2
#define BUF_SIZE (1024 * 2)
#define RD_BUF_SIZE (1024)
static QueueHandle_t uart2_queue;
static intr_handle_t handle_console;

static const char * TAG = "";                  
 
#define U2RXD 33
#define U2TXD 32
 
uint8_t rxbuf[256];     //Buffer di ricezione
uint16_t rx_fifo_len;        //Lunghezza dati
 
static void IRAM_ATTR uart_intr_handle(void *arg)
{
  uint16_t rx_fifo_len, status;
  uint16_t i=0;
  status = UART0.int_st.val; // read UART interrupt Status
  rx_fifo_len = UART0.status.rxfifo_cnt; // read number of bytes in UART buffer
  while(rx_fifo_len){
   rxbuf[i++] = UART0.fifo.rw_byte; // read all bytes
   rx_fifo_len--;
  }
}
void setup() {
 
    Serial.begin(115200);
 
    //Configuro la porta Serial2 (tutti i parametri hanno anche un get per effettuare controlli)
    uart_config_t Configurazione_UART2 = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_SO, &Configurazione_UART2);
    esp_log_level_set(TAG, ESP_LOG_INFO);
    //Cai Pin UART
    uart_set_pin(UART_SO, U2TXD, U2RXD, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    //Cai buffer
    uart_driver_install(UART_SO, BUF_SIZE, BUF_SIZE, 20, &uart2_queue, 0);
     // enble ngat uart
    uart_isr_free(UART_SO);
    uart_isr_register(UART_SO,uart_intr_handle, NULL, ESP_INTR_FLAG_IRAM, &handle_console);
    uart_enable_rx_intr(UART_SO);
    //Create a task to handler UART event from ISR
    xTaskCreate(UART_ISR_ROUTINE, "UART_ISR_ROUTINE", 2048, NULL, 12, NULL);
 
}
 
 
 
void loop() {
  Serial.println("Waiting data from  SERIAL 2....");
  delay(1000);
  }
 
 
 
 static void UART_ISR_ROUTINE(void *pvParameters)
{
    uart_event_t event;
    size_t buffered_size;
    bool exit_condition = false;
   
    //Infinite loop to run main bulk of task
    while (1) {
     
        
    }
   
    //Out side of loop now. Task needs to clean up and self terminate before returning
    vTaskDelete(NULL);
}
