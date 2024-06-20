/**
 * @file rs485.c
 * @author support@redisage.com
 * @brief RS485 example for ESP32 Open IoT and IIoT Gateway
 * 
 * @copyright 2024 Redisage Electronics - all rights reserved
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"

// MAX481 RS485 transceivers
#define UART_NUMS     UART_NUM_1, UART_NUM_2
#define UART_TX_PINS  GPIO_NUM_32, GPIO_NUM_5
#define UART_RX_PINS  GPIO_NUM_35, GPIO_NUM_37
#define UART_RTS_PINS GPIO_NUM_14, GPIO_NUM_12

// 74HC595BQ shift register used for termination enabling
#define CLK_GPIO      GPIO_NUM_33
#define DATA_GPIO     GPIO_NUM_4

#define HW_REVISION   4
#if HW_REVISION >= 3
#define LATCH_GPIO    GPIO_NUM_15
#else
#define LATCH_GPIO    GPIO_NUM_13
#endif

#define COM_NB 2

#define RX_BUF_SIZE 1024

#define TIMEOUT_MS (100 / portTICK_PERIOD_MS)

static const char* TAG = "rs485";


// set 74HC595BQ shift register
static void shift_reg_write_byte(uint8_t byte)
{
  gpio_set_level(LATCH_GPIO, 0);

  // feed storage register
  for (uint8_t i = 0; i < 8; i++)
  {
    gpio_set_level(DATA_GPIO, byte & (1 << (7 - i)));
    gpio_set_level(CLK_GPIO, 1);
    gpio_set_level(CLK_GPIO, 0);
  }

  gpio_set_level(LATCH_GPIO, 1); // push data to output
}


// line termination is set via 74HC595BQ shift register
void set_line_termination(uint8_t com_num, bool termination_enable, uint8_t* termination_state)
{
  uint8_t shift = 0;

  if (com_num == 0)
    shift = 7; // Q7
  else if (com_num == 1)
    shift = 3; // Q3
  else
  {
    ESP_LOGE(TAG, "wrong COM number");
    return;
  }

  if (termination_enable == false)
    *termination_state &= ~(1 << shift); // set 0
  else
    *termination_state |= (1 << shift); // set 1

  shift_reg_write_byte(*termination_state);
}


void app_main(void)
{
  ESP_LOGI(TAG, "initializing...");

  uint8_t rx_buf[COM_NB][RX_BUF_SIZE];

  // set UART as RS485
  uart_port_t uart_num[COM_NB] = {UART_NUMS};
  gpio_num_t uart_tx_pin[COM_NB] = {UART_TX_PINS};
  gpio_num_t uart_rx_pin[COM_NB] = {UART_RX_PINS};
  gpio_num_t uart_rts_pin[COM_NB] = {UART_RTS_PINS};

  // UART configuration
  uart_config_t uart_config_default = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .rx_flow_ctrl_thresh = 0,
    .source_clk = UART_SCLK_DEFAULT
  };

  // configure all UART ports
  for (uint8_t i = 0; i < COM_NB; i++)
  {
    ESP_ERROR_CHECK(uart_param_config(uart_num[i], &uart_config_default));
    ESP_ERROR_CHECK(uart_set_pin(uart_num[i], uart_tx_pin[i], uart_rx_pin[i], uart_rts_pin[i], UART_PIN_NO_CHANGE));
    ESP_ERROR_CHECK(uart_driver_install(uart_num[i], RX_BUF_SIZE * 2, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_set_mode(uart_num[i], UART_MODE_RS485_HALF_DUPLEX)); // needed for RS485 communication
  }

  // set RS485 line termination
  gpio_config_t io_conf = {
    .intr_type = GPIO_INTR_DISABLE,
    .mode = GPIO_MODE_OUTPUT,
    .pin_bit_mask = ((1ULL << CLK_GPIO) | (1ULL << DATA_GPIO) | (1ULL << LATCH_GPIO)),
    .pull_down_en = 0,
    .pull_up_en = 0
  };
  gpio_config(&io_conf);

  uint8_t termination_state = 0;
  for (uint8_t i = 0; i < COM_NB; i++)
    set_line_termination(i, false, &termination_state); // false - termination disabled; true - termination enabled

  ESP_LOGI(TAG, "init done");

  // test string to send
  uint8_t test_string[] = "test RS485 communication";
  uint32_t test_string_len = sizeof(test_string) / sizeof(test_string[0]);

  while (1)
  {
    for (uint8_t i = 0; i < COM_NB; i++)
    {
      uint8_t j = (i + 1) % COM_NB;

      // send RS485 message
      uart_write_bytes(uart_num[i], test_string, test_string_len);
      ESP_ERROR_CHECK(uart_wait_tx_done(uart_num[i], TIMEOUT_MS));

      // receive RS485 message
      int32_t len = uart_read_bytes(uart_num[j], rx_buf[j], test_string_len, TIMEOUT_MS);
      if (len == test_string_len)
        ESP_LOGI(TAG, "received on RS485 %u string: %s", j + 1, rx_buf[j]);
      else
        ESP_LOGE(TAG, "received wrong number of bytes: %ld/%lu", len, test_string_len);
    }
    printf("\n");

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}