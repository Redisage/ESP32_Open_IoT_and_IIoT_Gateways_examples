/**
 * @file ethernet_init.h
 * @author support@redisage.com
 * @brief Ethernet init for ESP32 Open IoT and IIoT Gateway
 * 
 * @copyright 2010-2022 Espressif Systems (Shanghai) CO LTD
 */

#pragma once

#include "esp_eth_driver.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize Ethernet driver based on Espressif IoT Development Framework Configuration
 *
 * @param[out] eth_handles_out array of initialized Ethernet driver handles
 * @param[out] eth_cnt_out number of initialized Ethernets
 * @return
 *          - ESP_OK on success
 *          - ESP_ERR_INVALID_ARG when passed invalid pointers
 *          - ESP_ERR_NO_MEM when there is no memory to allocate for Ethernet driver handles array
 *          - ESP_FAIL on any other failure
 */
esp_err_t example_eth_init(esp_eth_handle_t* eth_handles_out[], uint8_t* eth_cnt_out);

#ifdef __cplusplus
}
#endif
