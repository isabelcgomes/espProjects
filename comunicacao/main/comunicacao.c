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

WiFiClientSecure secured_client;

UniversalTelegramBot bot("7237030938:AAH7nEiM9WZIzozhfrJED417re8xceb7ipM", secured_client)

bool flag=false;

void setup(void)
{
    wifi_init();
    ESP_ERROR_CHECK(wifi_connect_sta("Francivaldo", "16172021", 10000));

    secure_client.setCACert(TELEGRAM_CERTIFICATE_ROOT)

    bot.sendMessage(1195145519, "Lembre de encher o potinho de água :)", "")
;
}