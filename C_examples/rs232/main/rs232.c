/**
 * @file rs232.c
 * @author support@redisage.com
 * @brief RS232 example for ESP32 Open IoT and IIoT Gateway
 * 
 * @copyright 2024 Redisage Electronics - all rights reserved
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define UART_NUMS     UART_NUM_1, UART_NUM_2
#define UART_TX_PINS  GPIO_NUM_32, GPIO_NUM_5
#define UART_RX_PINS  GPIO_NUM_35, GPIO_NUM_37

#define COM_NB 2

#define RX_BUF_SIZE 1024

#define TIMEOUT_MS (100 / portTICK_PERIOD_MS)

static const char* TAG = "rs232";


void app_main(void)
{
  ESP_LOGI(TAG, "initializing...");

  uint8_t rx_buf[COM_NB][RX_BUF_SIZE];

  uart_port_t uart_num[COM_NB] = {UART_NUMS};
  gpio_num_t uart_tx_pin[COM_NB] = {UART_TX_PINS};
  gpio_num_t uart_rx_pin[COM_NB] = {UART_RX_PINS};

  // UART configurations
  uart_config_t uart_config_default = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .rx_flow_ctrl_thresh = UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_DEFAULT
  };

  // configure all UART ports
  for (uint8_t i = 0; i < COM_NB; i++)
  {
    ESP_ERROR_CHECK(uart_param_config(uart_num[i], &uart_config_default));
    ESP_ERROR_CHECK(uart_set_pin(uart_num[i], uart_tx_pin[i], uart_rx_pin[i], UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    ESP_ERROR_CHECK(uart_driver_install(uart_num[i], RX_BUF_SIZE * 2, 0, 0, NULL, 0));
  }

  ESP_LOGI(TAG, "init done");

  // test string to send
  uint8_t test_string[] = "test RS232 communication";
  uint32_t test_string_len = sizeof(test_string) / sizeof(test_string[0]);

  while (1)
  {
    // send through RS232
    for (uint8_t i = 0; i < COM_NB; i++)
    {
      uart_write_bytes(uart_num[i], test_string, test_string_len);
      ESP_ERROR_CHECK(uart_wait_tx_done(uart_num[i], TIMEOUT_MS));
    }

    // receive from RS232
    for (uint8_t i = 0; i < COM_NB; i++)
    {
      int32_t len = uart_read_bytes(uart_num[i], rx_buf[i], test_string_len, TIMEOUT_MS);

      if (len == test_string_len)
        ESP_LOGI(TAG, "received on RS232 %u string: %s", i + 1, rx_buf[i]);
      else
        ESP_LOGE(TAG, "received wrong number of bytes: %ld/%lu", len, test_string_len);
    }
    printf("\n");

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}