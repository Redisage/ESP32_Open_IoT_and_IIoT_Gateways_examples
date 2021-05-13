/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"

#define CLK_GPIO            GPIO_NUM_33          /* SHCP */
#define DATA_GPIO           GPIO_NUM_4           /* DS */
#define LATCH_GPIO          GPIO_NUM_15          /* STCP */

/** Inits shift reg */
void shift_reg_write_byte(uint8_t byte){

  uint8_t i;

  gpio_set_level(LATCH_GPIO, 0);

  for(i = 0; i < 8; i++) {
    printf("%d\n", !!(byte & (1 << (7 - i))));
    gpio_set_level(DATA_GPIO, !!(byte & (1 << (7 - i))));

    gpio_set_level(CLK_GPIO, 1);
    gpio_set_level(CLK_GPIO, 0);
  }
      gpio_set_level(CLK_GPIO, 1);
    gpio_set_level(CLK_GPIO, 0);

  gpio_set_level(LATCH_GPIO, 1);
}

void init_shift_reg(void) {
  gpio_pad_select_gpio(CLK_GPIO);
  gpio_set_direction(CLK_GPIO, GPIO_MODE_OUTPUT);
  gpio_set_level(CLK_GPIO, 0);
  gpio_pad_select_gpio(DATA_GPIO);
  gpio_set_direction(DATA_GPIO, GPIO_MODE_OUTPUT);
  gpio_set_level(DATA_GPIO, 0);
  gpio_pad_select_gpio(LATCH_GPIO);
  gpio_set_direction(LATCH_GPIO, GPIO_MODE_OUTPUT);
  gpio_set_level(LATCH_GPIO, 1);
  shift_reg_write_byte(0x00);
}


void app_main(void)
{
    printf("Hello world!\n");

    init_shift_reg();
    printf("\n\n");

    shift_reg_write_byte(0x70);
}
