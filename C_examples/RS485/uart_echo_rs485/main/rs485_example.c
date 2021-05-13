#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "driver/uart.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "driver/gpio.h."


// Receiver - UART1
#define RECEIVER_TAG                    "RS485_RECEIVER_APP"
#define RS485_RECEIVER_TXD              (GPIO_NUM_32)
#define RS485_RECEIVER_RXD              (GPIO_NUM_35)
#define RECEIVER_PORT                   (1)
#define RECEIVER_TASK_PRIO              (10)
#define RECEIVER_TASK_STACK_SIZE        (2048)

// Sender - UART2
#define SENDER_TAG                      "RS485_SENDER_APP"
#define RS485_SENDER_TXD                (GPIO_NUM_5)
#define RS485_SENDER_RXD                (GPIO_NUM_37)
#define SENDER_PORT                     (2)
#define SENDER_TASK_PRIO                (11)
#define SENDER_TASK_STACK_SIZE          (2048)

//RTS for RS485 Half-Duplex Mode manages DE/~RE
#define RS485_RECEIVER_RTS   (GPIO_NUM_14)
#define RS485_SENDER_RTS     (GPIO_NUM_12)

/* CTS is not used in RS485 Half-Duplex Mode */
#define RS485_RECEIVER_CTS   (UART_PIN_NO_CHANGE)
#define RS485_SENDER_CTS     (UART_PIN_NO_CHANGE)

#define BUF_SIZE        (127)
#define BAUD_RATE       (115200)

/* Read packet timeout */
#define PACKET_READ_TICS        (3000 / portTICK_RATE_MS)

// Timeout threshold for UART = number of symbols (~10 tics) with unchanged state on receive pin
#define ECHO_READ_TOUT          (3) // 3.5T * 8 = 28 ticks, TOUT=3 -> ~24..33 ticks

// An example of receiver with hardware flow control on UART
static void receiver_task(void *arg)
{
    const int uart_num = RECEIVER_PORT;
    uart_config_t uart_config = {
        .baud_rate = BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
        .source_clk = UART_SCLK_APB,
    };

    // Set UART log level
    esp_log_level_set(RECEIVER_TAG, ESP_LOG_INFO);

    ESP_LOGI(RECEIVER_TAG, "Start RS485 Receiver application and configure UART.");

    // Install UART driver (we don't need an event queue here)
    // In this example we don't even use a buffer for sending data.
    ESP_ERROR_CHECK(uart_driver_install(uart_num, BUF_SIZE * 2, 0, 0, NULL, 0));

    // Configure UART parameters
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));

    ESP_LOGI(RECEIVER_TAG, "UART set pins, mode and install driver.");

    // Set UART pins as per KConfig settings
    ESP_ERROR_CHECK(uart_set_pin(uart_num, RS485_RECEIVER_TXD, RS485_RECEIVER_RXD, RS485_RECEIVER_CTS, RS485_RECEIVER_CTS));

    // Set RS485 half duplex mode
    ESP_ERROR_CHECK(uart_set_mode(uart_num, UART_MODE_RS485_HALF_DUPLEX));

    // Set read timeout of UART TOUT feature
    ESP_ERROR_CHECK(uart_set_rx_timeout(uart_num, ECHO_READ_TOUT));

    // Allocate buffers for UART
    uint8_t* data = (uint8_t*) malloc(BUF_SIZE);

    ESP_LOGI(RECEIVER_TAG, "UART start recieve loop.\r\n");

    /* Set the Sender RTS Pin High to drive RS485 Converter */
    gpio_pad_select_gpio(RS485_RECEIVER_RTS);
    gpio_set_direction(RS485_RECEIVER_RTS, GPIO_MODE_OUTPUT);
    gpio_set_level(RS485_RECEIVER_RTS, 0);

    while(1) {
        //Read data from UART
        int len = uart_read_bytes(uart_num, data, BUF_SIZE, PACKET_READ_TICS);

        if (len > 0) {
            ESP_LOGI(RECEIVER_TAG, "Received %u bytes:", len);
            for (int i = 0; i < len; i++) {
                printf("0x%.2X ", (uint8_t)data[i]);
            }
            printf("\n");
        }
        else {
            // Print . to show we are alive while no message is send
            ESP_LOGI(RECEIVER_TAG, "No message arrived.");
            ESP_ERROR_CHECK(uart_wait_tx_done(uart_num, 10));
        }
    }
    vTaskDelete(NULL);
}

// An example of sender with hardware flow control on UART
static void sender_task(void *arg)
{

    const int uart_num = SENDER_PORT;
    uart_config_t uart_config = {
        .baud_rate = BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
        .source_clk = UART_SCLK_APB,
    };

    // Set UART log level
    esp_log_level_set(SENDER_TAG, ESP_LOG_INFO);

    ESP_LOGI(SENDER_TAG, "Start RS485 Sender application and configure UART.");

    // Install UART driver (we don't need an event queue here)
    // In this example we don't even use a buffer for sending data.
    ESP_ERROR_CHECK(uart_driver_install(uart_num, BUF_SIZE * 2, 0, 0, NULL, 0));

    // Configure UART parameters
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));

    ESP_LOGI(SENDER_TAG, "UART set pins, mode and install driver.");

    // Set UART pins as per KConfig settings
    ESP_ERROR_CHECK(uart_set_pin(uart_num, RS485_SENDER_TXD, RS485_SENDER_RXD, RS485_SENDER_RTS, RS485_SENDER_CTS));

    // Set RS485 half duplex mode
    ESP_ERROR_CHECK(uart_set_mode(uart_num, UART_MODE_RS485_HALF_DUPLEX));

    ESP_LOGI(SENDER_TAG, "UART start sender loop.\r\n");

    /* Set the Sender RTS Pin High to drive RS485 Converter */
    gpio_pad_select_gpio(RS485_SENDER_RTS);
    gpio_set_direction(RS485_SENDER_RTS, GPIO_MODE_OUTPUT);
    gpio_set_level(RS485_SENDER_RTS, 1);

    while(1) {
        ESP_LOGI(SENDER_TAG, "Sending message..");

        uint8_t data[BUF_SIZE];
        uint8_t x = 0;

        for(x = 0; x < BUF_SIZE; x++){
            data[x] = 0x23;
        }

        uart_write_bytes(uart_num, (const char *)data, BUF_SIZE);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}


void app_main(void)
{
    /* Receiver task */
    xTaskCreate(receiver_task, "rs485_receiver_task", RECEIVER_TASK_STACK_SIZE, NULL, RECEIVER_TASK_PRIO, NULL);

    /* Sender task */
    xTaskCreate(sender_task, "rs485_sender_task", SENDER_TASK_STACK_SIZE, NULL, SENDER_TASK_PRIO, NULL);
}
