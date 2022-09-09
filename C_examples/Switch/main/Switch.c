/* Switch Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"



#define SERIAL_REG_DATA 4
#define STCP 15
#define SHCP 33
#define BUTTON 34

#define SHIFT_REGISTER_BUFFER_LENGTH 8
#define RED 6
#define BLUE 5
#define GREEN 4


bool shift_register_buffer[SHIFT_REGISTER_BUFFER_LENGTH];   //only 3 of 8 pins in shift register reserved for rgb LED

static void app_gpio_init(void){
    gpio_pad_select_gpio(STCP);
    gpio_set_direction(SERIAL_REG_DATA, GPIO_MODE_OUTPUT);
    gpio_set_direction(STCP, GPIO_MODE_OUTPUT);
    gpio_set_direction(SHCP, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
}

static void shift_register_set_buffer(void){
    gpio_set_level(STCP, 0);
    for(int i = 7; i >= 0; i--){
        gpio_set_level(SHCP, 0);
        gpio_set_level(SERIAL_REG_DATA, shift_register_buffer[i]);
        gpio_set_level(SHCP, 1);
    }
    gpio_set_level(STCP, 1);
}

static void shift_register_clear_buffer(void){
    for(int i = 0; i < SHIFT_REGISTER_BUFFER_LENGTH; i++){
        shift_register_buffer[i] = 0;
    }
}

static void set_color(int x){
    shift_register_clear_buffer();
    shift_register_buffer[x] = 1;
    shift_register_set_buffer();
}

void app_main(void)
{
    app_gpio_init();
    while (1) {
        if(gpio_get_level(BUTTON) == 1){
            set_color(RED);

        }else{
            shift_register_clear_buffer();
            shift_register_set_buffer();
        }

    }
}
