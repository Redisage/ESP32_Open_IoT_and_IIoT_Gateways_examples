/* UART Echo Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"

/* Receiver - UART1 */
#define RECEIVER_TAG                    "RS232_RECEIVER_APP"
#define RS232_RECEIVER_TXD              (GPIO_NUM_32)
#define RS232_RECEIVER_RXD              (GPIO_NUM_35)
#define RS232_RECEIVER_RTS              (GPIO_NUM_14)
#define RS232_RECEIVER_CTS              (UART_PIN_NO_CHANGE)
#define RECEIVER_PORT                   (1)
#define RECEIVER_TASK_PRIO              (10)
#define RECEIVER_TASK_STACK_SIZE        (2048)

/* Sender - UART2 */
#define SENDER_TAG                      "RS2323_SENDER_APP"
#define RS232_SENDER_TXD                (GPIO_NUM_5)
#define RS232_SENDER_RXD                (GPIO_NUM_37)
#define RS232_SENDER_RTS                (GPIO_NUM_12)
#define RS232_SENDER_CTS                (UART_PIN_NO_CHANGE)
#define SENDER_PORT                     (2)
#define SENDER_TASK_PRIO                (11)
#define SENDER_TASK_STACK_SIZE          (2048)

#define BUF_SIZE (127)

#define PACKET_READ_TICS        (1000 / portTICK_RATE_MS)

static void receiver_task(void *arg)
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    uart_driver_install(UART_NUM_1, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, RS232_RECEIVER_TXD, RS232_RECEIVER_RXD, RS232_RECEIVER_RTS, RS232_RECEIVER_CTS);

    // Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);

    ESP_LOGI(SENDER_TAG, "Start RS232 Receiver application");

    while (1) {
        // Read data from the UART
        int len = uart_read_bytes(RECEIVER_PORT, data, BUF_SIZE, PACKET_READ_TICS);

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
            ESP_ERROR_CHECK(uart_wait_tx_done(RECEIVER_PORT, 10));
        }
    }

    vTaskDelete(NULL);
}


static void sender_task(void *arg)
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    uart_driver_install(UART_NUM_2, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_2, &uart_config);
    uart_set_pin(UART_NUM_2, RS232_SENDER_TXD, RS232_SENDER_RXD, RS232_SENDER_RTS, RS232_SENDER_CTS);

    ESP_LOGI(SENDER_TAG, "Start RS232 Sender application");

    while (1) {

        ESP_LOGI(SENDER_TAG, "Sending message..");

        uint8_t data[BUF_SIZE];
        uint8_t x = 0;

        for(x = 0; x < BUF_SIZE; x++){
            data[x] = 0x23;
        }

        uart_write_bytes(SENDER_PORT, (const char *) data, BUF_SIZE);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    /* Receiver task */
    xTaskCreate(receiver_task, "rs232_receiver_task", RECEIVER_TASK_STACK_SIZE, NULL, 10, NULL);

    /* Sender task */
    xTaskCreate(sender_task, "rs232_sender_task", SENDER_TASK_STACK_SIZE, NULL, 11, NULL);
}
