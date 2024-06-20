/**
 * @file rgb_led.c
 * @author support@redisage.com
 * @brief RGB LED example for ESP32 Open IoT and IIoT Gateway
 * 
 * @copyright 2024 Redisage Electronics - all rights reserved
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define CLK_GPIO GPIO_NUM_33
#define DATA_GPIO GPIO_NUM_4

#define HW_REVISION 4 // hardware version

#if HW_REVISION >= 3
#define LATCH_GPIO GPIO_NUM_15
#else
#define LATCH_GPIO GPIO_NUM_13
#endif

static const char* TAG = "rgb_led";


// RGB LED is controlled via 74HC595BQ shift register
void shift_reg_write_byte(uint8_t byte)
{
  gpio_set_level(LATCH_GPIO, 0);

  // feed storage register
  for (uint8_t i = 0; i < 8; i++)
  {
    gpio_set_level(DATA_GPIO, (byte & (1 << (7 - i))));
    gpio_set_level(CLK_GPIO, 1);
    gpio_set_level(CLK_GPIO, 0);
  }

  gpio_set_level(LATCH_GPIO, 1); // push data to output
}


void app_main(void)
{
  ESP_LOGI(TAG, "initializing...");

  // init GPIOs
  gpio_config_t io_conf = {
    .intr_type = GPIO_INTR_DISABLE,
    .mode = GPIO_MODE_OUTPUT,
    .pin_bit_mask = ((1ULL << CLK_GPIO) | (1ULL << DATA_GPIO) | (1ULL << LATCH_GPIO)),
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .pull_up_en = GPIO_PULLUP_DISABLE
  };
  gpio_config(&io_conf);

  gpio_set_level(CLK_GPIO, 0);
  gpio_set_level(DATA_GPIO, 0);
  gpio_set_level(LATCH_GPIO, 1);

  ESP_LOGI(TAG, "init done\n");

  // change LED colors
  while (1)
  {
    ESP_LOGI(TAG, "led red");
    shift_reg_write_byte(0b01000000);
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    ESP_LOGI(TAG, "led green");
    shift_reg_write_byte(0b00010000);
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    ESP_LOGI(TAG, "led blue\n");
    shift_reg_write_byte(0b00100000);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}