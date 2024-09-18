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
#include <UniversalTelegramBot.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

#define UMIDADE 13
#define LED 2
#define LUZ 32
#define TEMPERATURA 26
#define SENSOR_TYPE DHT_TYPE_DHT11

int i;
float umidadeDigital, luzDigital, temperaturaDigital, temperature, humidity;

void app_main(void)
{
    wifi_init();
    ESP_ERROR_CHECK(wifi_connect_sta("Francivaldo", "16172021", 10000));

}