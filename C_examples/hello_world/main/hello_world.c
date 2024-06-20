/**
 * @file hello_world.c
 * @author support@redisage.com
 * @brief Hello World example for ESP32 Open IoT and IIoT Gateway
 * 
 * @copyright 2010-2022 Espressif Systems (Shanghai) CO LTD
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_log.h"

static const char* TAG = "hello_world";


void app_main(void)
{
  ESP_LOGI(TAG, "Hello world!\n");

  // print chip information
  esp_chip_info_t chip_info;
  uint32_t flash_size;
  esp_chip_info(&chip_info);
  ESP_LOGI(TAG, "This is %s chip with %d CPU core(s), %s%s%s%s, ",
                                                      CONFIG_IDF_TARGET,
                                                      chip_info.cores,
                                                      (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
                                                      (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
                                                      (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
                                                      (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

  uint16_t major_rev = chip_info.revision / 100;
  uint16_t minor_rev = chip_info.revision % 100;
  ESP_LOGI(TAG, "silicon revision v%u.%u, ", major_rev, minor_rev);

  if (esp_flash_get_size(NULL, &flash_size) != ESP_OK)
  {
    ESP_LOGI(TAG, "Get flash size failed");
    return;
  }

  ESP_LOGI(TAG, "%lu MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
          (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

  ESP_LOGI(TAG, "Minimum free heap size: %lu bytes\n", esp_get_minimum_free_heap_size());

  for (int16_t i = 10; i >= 0; i--)
  {
    ESP_LOGI(TAG, "Restarting in %d seconds...\n", i);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

  ESP_LOGI(TAG, "Restarting now.\n");
  fflush(stdout);
  esp_restart();
}
