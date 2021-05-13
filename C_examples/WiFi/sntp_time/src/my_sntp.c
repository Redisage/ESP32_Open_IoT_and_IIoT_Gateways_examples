/**
 ******************************************************************************
 * @file       my_sntp.c
 * @author     Pawel Wojciechowski / B.P.I. SoftCad
 * @brief      Services the SNTP protocol.
 ******************************************************************************
 * @attention
 * COPYRIGHT 2021 B.P.I. SoftCad. All rights reserved.
 * CONTACT-INFO: info@softcad.com.pl
 ******************************************************************************
 */

#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_attr.h"
#include "esp_sleep.h"
#include "nvs_flash.h"
#include "esp_sntp.h"

#include "my_sntp.h"


const char *SNTP_TAG = "SNTP";

void initialize_sntp(void)
{
    ESP_LOGI(SNTP_TAG, "Initializing SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);

    sntp_init();
}

void obtain_time(void)
{
    initialize_sntp();

    // wait for time to be set
    time_t now = 0;
    struct tm timeinfo = {0};
    int retry = 0;
    const int retry_count = 3;
    while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && retry < retry_count) {       /* && ++retry < retry_count */
        ESP_LOGI(SNTP_TAG, "Waiting for system time to be set... %d", retry++ );            /* retry_count */
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }

    sntp_stop();

    time(&now);
    localtime_r(&now, &timeinfo);
}

void time_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI(SNTP_TAG, "Notification of a time synchronization event");
}
