/**
 * @file switch.c
 * @author support@redisage.com
 * @brief Switch example for ESP32 Open IoT and IIoT Gateway
 * 
 * @copyright 2024 Redisage Electronics - all rights reserved
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define SWITCH_GPIO 34

#define QUEUE_LEN 10
#define TIMEOUT_MS (100 / portTICK_PERIOD_MS)

static const char* TAG = "switch";


// interrupt handler
static void IRAM_ATTR gpio_isr_handler(void* arg)
{
  QueueHandle_t queue = (QueueHandle_t)arg;

  bool switch_change = true;

  // send information from interrupt to queue
  if (xQueueSend(queue, &switch_change, TIMEOUT_MS) == pdFALSE)
    ESP_LOGE(TAG, "Failed to send queue");
}


void app_main(void)
{
  bool switch_state = true;
  bool switch_change = false;

  // init queue
  QueueHandle_t queue = xQueueCreate(QUEUE_LEN, sizeof(switch_change));
  if (queue == NULL)
  {
    ESP_LOGE(TAG, "Failed to create queue");
    return;
  }

  // init gpio with interrupt
  gpio_config_t io_conf = {
    .intr_type = GPIO_INTR_ANYEDGE,
    .mode = GPIO_MODE_INPUT,
    .pin_bit_mask = (1ULL << SWITCH_GPIO),
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .pull_up_en = GPIO_PULLUP_ENABLE
  };
  gpio_config(&io_conf);
  gpio_install_isr_service(0);
  gpio_isr_handler_add(SWITCH_GPIO, gpio_isr_handler, queue);

  // main loop
  while (1)
  {
    // receive from queue
    if (xQueueReceive(queue, &switch_change, portMAX_DELAY) == pdTRUE)
    {
      if (switch_change)
      {
        if (switch_state)
          ESP_LOGI(TAG, "switch pressed");
        else
          ESP_LOGI(TAG, "switch released\n");

        switch_state = !switch_state;
        switch_change = false;
      }
    }
    else
      ESP_LOGE(TAG, "Failed to receive from queue");
  }
}