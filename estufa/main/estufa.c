/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "dht.h"

#define UMIDADE 13
#define LED 2
#define LUZ 32
#define TEMPERATURA 26
#define SENSOR_TYPE DHT_TYPE_DHT11

int i;
float umidadeDigital, luzDigital, temperaturaDigital, temperature, humidity;

void app_main(void)
{
        while (true)
        {
            dht_read_float_data(SENSOR_TYPE, TEMPERATURA, &humidity, &temperature);

            esp_rom_gpio_pad_select_gpio(UMIDADE);
            gpio_set_direction(UMIDADE, GPIO_MODE_INPUT);

            esp_rom_gpio_pad_select_gpio(LUZ);
            gpio_set_direction(LUZ, GPIO_MODE_INPUT);

            esp_rom_gpio_pad_select_gpio(LED);
            gpio_set_direction(LED, GPIO_MODE_OUTPUT);

            umidadeDigital = gpio_get_level(UMIDADE);
            luzDigital = gpio_get_level(LUZ);
            temperaturaDigital = gpio_get_level(TEMPERATURA);

            if (umidadeDigital == 1 && luzDigital == 0 && humidity <= 50)
            {
                gpio_set_level(LED, 1);
            }
            else
            {
                gpio_set_level(LED, 0);
            }

            printf("Umidade: %f \n", umidadeDigital);
            printf("Luz: %f \n", luzDigital);
            printf("Temperatura: %f \n", temperaturaDigital);

            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }