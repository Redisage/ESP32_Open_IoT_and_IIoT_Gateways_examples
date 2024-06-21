/**
 * @file i2c_scanner.c
 * @author support@redisage.com
 * @brief I2C scanner example for ESP32 Open IoT and IIoT Gateway
 * 
 * @copyright 2024 Redisage Electronics - all rights reserved
 */


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "esp_log.h"

#define I2C_NUM I2C_NUM_1
#define SCL_PIN GPIO_NUM_2
#define SDA_PIN GPIO_NUM_13

#define I2C_FREQ 100000
#define TIMEOUT_MS 10

#define SKIP_ADDRESS 0x50

static const char* TAG = "i2c_scanner";


void app_main(void)
{
  bool lis3dh_found   = false;
  bool si7006_found   = false;
  bool eeprom_found   = false;
  bool hts221_found   = false;
  bool lsm6ds33_found = false;

  ESP_LOGD(TAG, ">> i2cScanner");

  // configure I2C bus
  i2c_master_bus_config_t i2c_mst_config = {
      .clk_source = I2C_CLK_SRC_DEFAULT,
      .i2c_port = I2C_NUM,
      .scl_io_num = SCL_PIN,
      .sda_io_num = SDA_PIN,
      .glitch_ignore_cnt = 7,
      .flags.enable_internal_pullup = true
  };
  i2c_master_bus_handle_t bus_handle;
  ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));

  esp_err_t espRc;
  printf("\n     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");
  printf("00:         ");

  // look for I2C devices
  for (uint8_t i = 0x03; i < 0x78; i++)
  {
    i2c_master_dev_handle_t dev_handle;
    if (i != SKIP_ADDRESS) // DFN5 package of EEPROM
    {
      // add new device to the bus
      i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = i,
        .scl_speed_hz = I2C_FREQ
      };
      ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle));

      // chech if device is present
      espRc = i2c_master_probe(bus_handle, dev_cfg.device_address, TIMEOUT_MS);
    }
    else
      espRc = ESP_FAIL;

    if (i % 16 == 0)
      printf("\n%.2x:", i);

    if (espRc == ESP_OK)
    {
      if (i == 0x18 || i == 0x19)
        lis3dh_found = true;
      else if (i == 0x40)
        si7006_found = true;
      else if (i == 0x54)
        eeprom_found = true;
      else if (i == 0x5F)
        hts221_found = true;
      else if (i == 0x6B)
        lsm6ds33_found = true;

      printf(" %.2x", i);
    }
    else
      printf(" --");

    ESP_LOGD(TAG, "i=%d, rc=%d (0x%x)", i, espRc, espRc);

    // remove device from bus
    if (i != SKIP_ADDRESS) // DFN5 package of EEPROM
      ESP_ERROR_CHECK(i2c_master_bus_rm_device(dev_handle));
  }
  printf("\r\n\r\n");

  // print if devices are present
  if (lis3dh_found)
    ESP_LOGI(TAG, "LIS3DH found");
  if (si7006_found)
    ESP_LOGI(TAG, "Si7006 found");
  if (eeprom_found)
    ESP_LOGI(TAG, "EEPROM found");
  if (hts221_found)
    ESP_LOGI(TAG, "HTS221 found");
  if (lsm6ds33_found)
    ESP_LOGI(TAG, "LSM6DS33 found");
}