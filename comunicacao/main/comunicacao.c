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

static const char *TAG = "telegram_bot";

#define WIFI_SSID "BEL"
#define WIFI_PASS "lavagirl"
#define BOT_TOKEN "7237030938:AAH7nEiM9WZIzozhfrJED417re8xceb7ipM"
#define CHAT_ID "1195145519"


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

    // Aguardar um tempo para garantir a conexão Wi-Fi
    vTaskDelay(10000 / portTICK_PERIOD_MS);

    // Enviar mensagem
    const char *message = "Lembre%20De%20Colocar%20Agua%20No%20Potinho";
    send_telegram_message(message);
}
