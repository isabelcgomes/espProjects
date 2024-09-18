#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <esp_system.h>
#include <esp_log.h>
#include <nvs_flash.h>
#include <esp_wifi.h>
#include <protocol_examples_common.h>
#include <esp_http_client.h>
#include "connect.h"
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "dht.h"


static const char *TAG = "telegram_bot";

#define WIFI_SSID "BEL"
#define WIFI_PASS "lavagirl"
#define BOT_TOKEN "7237030938:AAH7nEiM9WZIzozhfrJED417re8xceb7ipM"
#define CHAT_ID "1195145519"
#define UMIDADE 13
#define LED 2
#define LUZ 32
#define TEMPERATURA 26
#define SENSOR_TYPE DHT_TYPE_DHT11
#define NIVEL 15

int i;
float umidadeDigital, luzDigital, temperaturaDigital, temperature, humidity, nivel;


static esp_err_t send_telegram_message(const char *message)
{
    char url[256];
    snprintf(url, sizeof(url), "https://api.telegram.org/bot%s/sendMessage?chat_id=%s&text=%s", BOT_TOKEN, CHAT_ID, message);

    esp_http_client_config_t config = {
        .url = url,
        .method = HTTP_METHOD_GET,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK)
    {
        ESP_LOGI(TAG, "Mensagem enviada com sucesso");
    }
    else
    {
        ESP_LOGE(TAG, "Erro ao enviar mensagem: %s", esp_err_to_name(err));
    }

    esp_http_client_cleanup(client);
    return err;
}


void app_main(void)
{
        ESP_ERROR_CHECK(nvs_flash_init());
        wifi_init();
        ESP_ERROR_CHECK(wifi_connect_sta("BEL", "lavagirl", 10000));

        vTaskDelay(10000 / portTICK_PERIOD_MS);

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
                nivel = gpio_get_level(NIVEL);
                if (nivel == 0){
                    const char *message = "Lembre%20De%20Colocar%20Agua%20No%20Potinho";
                    send_telegram_message(message);
                    gpio_set_level(LED, 1);
                }
                else{
                    gpio_set_level(LED, 1);
                }


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
