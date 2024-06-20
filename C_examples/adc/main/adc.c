/**
 * @file adc.c
 * @author support@redisage.com
 * @brief ADC example for ESP32 Open IoT and IIoT Gateway
 * 
 * @copyright 2024 Redisage Electronics - all rights reserved
 */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_adc/adc_continuous.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_log.h"

#define DEFAULT_V_REF            1100
#define READ_LEN                 256
#define ADC_UNIT                 ADC_UNIT_1
#define _ADC_UNIT_STR(unit)      #unit
#define ADC_UNIT_STR(unit)       _ADC_UNIT_STR(unit)
#define ADC_CONV_MODE            ADC_CONV_SINGLE_UNIT_1
#define ADC_ATTEN                ADC_ATTEN_DB_12
#define ADC_BIT_WIDTH            SOC_ADC_DIGI_MAX_BITWIDTH
#define ADC_OUTPUT_TYPE          ADC_DIGI_OUTPUT_FORMAT_TYPE1
#define ADC_GET_CHANNEL(p_data)  ((p_data)->type1.channel)
#define ADC_GET_DATA(p_data)     ((p_data)->type1.data)

static TaskHandle_t s_task_handle;

static const char* TAG = "adc";


// ADC conversion callback
static bool IRAM_ATTR s_conv_done_cb(adc_continuous_handle_t handle, const adc_continuous_evt_data_t* edata, void* user_data)
{
  BaseType_t mustYield = pdFALSE;
  // notify that ADC continuous driver has done enough number of conversions
  vTaskNotifyGiveFromISR(s_task_handle, &mustYield);

  return (mustYield == pdTRUE);
}


// initialize continuous ADC driver
static void continuous_adc_init(adc_channel_t* channel, uint8_t channel_num, adc_continuous_handle_t* out_handle)
{
  adc_continuous_handle_t handle = NULL;

  adc_continuous_handle_cfg_t adc_config = {
    .max_store_buf_size = 1024,
    .conv_frame_size = READ_LEN
  };
  ESP_ERROR_CHECK(adc_continuous_new_handle(&adc_config, &handle));

  adc_continuous_config_t dig_cfg = {
    .sample_freq_hz = 20 * 1000,
    .conv_mode = ADC_CONV_MODE,
    .format = ADC_OUTPUT_TYPE
  };

  adc_digi_pattern_config_t adc_pattern[SOC_ADC_PATT_LEN_MAX] = {0};
  dig_cfg.pattern_num = channel_num;
  for (int i = 0; i < channel_num; i++)
  {
    adc_pattern[i].atten = ADC_ATTEN;
    adc_pattern[i].channel = channel[i] & 0x7;
    adc_pattern[i].unit = ADC_UNIT;
    adc_pattern[i].bit_width = ADC_BIT_WIDTH;

    ESP_LOGI(TAG, "adc_pattern[%d].atten is: %u", i, adc_pattern[i].atten);
    ESP_LOGI(TAG, "adc_pattern[%d].channel is: %u", i, adc_pattern[i].channel);
    ESP_LOGI(TAG, "adc_pattern[%d].unit is: %u", i, adc_pattern[i].unit);
  }
  dig_cfg.adc_pattern = adc_pattern;
  ESP_ERROR_CHECK(adc_continuous_config(handle, &dig_cfg));

  *out_handle = handle;
}


void app_main()
{
  esp_err_t ret;
  uint32_t ret_num = 0;
  uint8_t result[READ_LEN] = {0};
  memset(result, 0xcc, READ_LEN);

  s_task_handle = xTaskGetCurrentTaskHandle();

  // init continuous ADC driver
  adc_channel_t channel[] = {ADC_CHANNEL_0};
  adc_continuous_handle_t adc_handle = NULL;
  continuous_adc_init(channel, sizeof(channel) / sizeof(adc_channel_t), &adc_handle);

  // init ADC callback
  adc_continuous_evt_cbs_t cbs = {
    .on_conv_done = s_conv_done_cb
  };
  ESP_ERROR_CHECK(adc_continuous_register_event_callbacks(adc_handle, &cbs, NULL));
  ESP_ERROR_CHECK(adc_continuous_start(adc_handle));

  // init ADC calibration
  adc_cali_handle_t adc_cali_handle;
  ESP_LOGI(TAG, "calibration scheme version is %s", "Line Fitting");
  adc_cali_line_fitting_config_t cali_config = {
    .unit_id = ADC_UNIT,
    .atten = ADC_ATTEN,
    .bitwidth = ADC_BIT_WIDTH
  };
  ESP_ERROR_CHECK(adc_cali_create_scheme_line_fitting(&cali_config, &adc_cali_handle));

  // main loop
  while (1)
  {
    // wait for data to be ready
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    char unit[] = ADC_UNIT_STR(ADC_UNIT);

    while (1)
    {
      ret = adc_continuous_read(adc_handle, result, READ_LEN, &ret_num, 0);
      if (ret == ESP_OK)
      {
        ESP_LOGI("TASK", "ret is %x, ret_num is %lu bytes", ret, ret_num);
        for (int i = 0; i < ret_num; i += SOC_ADC_DIGI_RESULT_BYTES)
        {
          adc_digi_output_data_t* p = (adc_digi_output_data_t*)&result[i];
          uint32_t chan_num = ADC_GET_CHANNEL(p);
          uint32_t data = ADC_GET_DATA(p);
          int voltage = 0;

          // check the channel number validation, the data is invalid if the channel num exceed the maximum channel
          if (chan_num < SOC_ADC_CHANNEL_NUM(ADC_UNIT))
          {
            // convert raw reading to voltage
            ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc_cali_handle, data, &voltage));
            ESP_LOGI(TAG, "Unit: %s, Channel: %lu, Raw Reading: %lu, Calibrated Voltage: %d mV", unit, chan_num, data, voltage);
          }
          else
            ESP_LOGW(TAG, "Invalid data [%s_%lu_%lu]", unit, chan_num, data);
        }

        vTaskDelay(1); // wait for ESP_LOG
      }
      else if (ret == ESP_ERR_TIMEOUT) // try to read `READ_LEN` until API returns timeout (there is no available data anymore)
        break;
    }
  }

  // deinit ADC
  ESP_ERROR_CHECK(adc_continuous_stop(adc_handle));
  ESP_ERROR_CHECK(adc_continuous_deinit(adc_handle));
  ESP_ERROR_CHECK(adc_cali_delete_scheme_line_fitting(adc_cali_handle));
}