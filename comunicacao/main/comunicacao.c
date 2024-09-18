// // #include <stdio.h>
// // #include "connect.h"
// // #include "nvs_flash.h"
// // #include "esp_log.h"
// // #include "esp_http_server.h"

// // const char *ssid = "SABAT_2G";
// // const char *senha = "378687030";
// // // adicione ID de bate-papo do Telegram + chave de API
// // char chat_id[] = "1195145519";
// // char api_key[] = "7237030938:AAH7nEiM9WZIzozhfrJED417re8xceb7ipM ";

// // void send_telegram_message(char mensagem[])
// // {
// //     httpd_start()
// //     char API_URL[] = api_key + "&text =" +urlEncode(mensagem) + "&chatId =" + chat_id;
// //     HTTPCliente http;
// //     http.begin(API_URL);
// //     http.addHeader("Tipo de conteúdo", "aplicativo / x - www - form - urlencoded");
// //     int http_response_code = http.GET;
// //     http.end;
// // }

// // void app_main(void)
// // {
// //     ESP_ERROR_CHECK(nvs_flash_init());
// //     wifi_init();
// //     ESP_ERROR_CHECK(wifi_connect_sta(ssid, senha, 10000));
// //     send_telegram_message("Lembra de colocar água no potinho");
// // }

// #include <stdio.h>
// #include <string.h>
// #include <esp_system.h>
// #include <esp_log.h>
// #include <nvs_flash.h>
// #include <esp_wifi.h>
// #include <protocol_examples_common.h>
// #include <esp_http_client.h>

// static const char *TAG = "telegram_bot";

// // Substitua pelas suas credenciais Wi-Fi
// #define WIFI_SSID "BEL"
// #define WIFI_PASS "lavagirl"

// // Substitua pelo seu token e chat ID
// #define BOT_TOKEN "7237030938:AAH7nEiM9WZIzozhfrJED417re8xceb7ipM"
// #define CHAT_ID "1195145519"

// // Função para enviar a mensagem para o Telegram
// esp_err_t send_telegram_message(const char *message)
// {
//     char url[] = "https://api.telegram.org/bot7237030938:AAH7nEiM9WZIzozhfrJED417re8xceb7ipM/sendMessage?chat_id=1195145519&text=Agua";
//     snprintf(url, sizeof(url), "https://api.telegram.org/bot%s/sendMessage?chat_id=%s&text=%s", BOT_TOKEN, CHAT_ID, message);

//     esp_http_client_config_t config = {
//         .url = url,
//         .method = HTTP_METHOD_POST,
//     };

//     esp_http_client_handle_t client = esp_http_client_init(&config);
//     esp_err_t err = esp_http_client_perform(client);

//     if (err == ESP_OK)
//     {
//         ESP_LOGI(TAG, "Mensagem enviada com sucesso");
//     }
//     else
//     {
//         ESP_LOGE(TAG, "Erro ao enviar mensagem: %s", esp_err_to_name(err));
//     }

//     esp_http_client_cleanup(client);
//     return err;
// }

// void app_main(void)
// {
//     // Inicializa a memória não volátil
//     nvs_flash_init();

//     // Configura a conexão Wi-Fi
//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     esp_wifi_init(&cfg);
//     esp_wifi_set_mode(WIFI_MODE_STA);
//     esp_wifi_set_config(WIFI_IF_STA, &(wifi_config_t){
//                                          .sta = {
//                                              .ssid = WIFI_SSID,
//                                              .password = WIFI_PASS,
//                                          },
//                                      });
//     esp_wifi_start();
//     esp_wifi_connect();

//     ESP_LOGI(TAG, "Conectando ao Wi-Fi...");

//     // Aguarde a conexão
//     vTaskDelay(10000 / portTICK_PERIOD_MS);

//     // Envie a mensagem
//     send_telegram_message("Agua");
// }

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

// static void wifi_init(void)
// {
//     ESP_ERROR_CHECK(nvs_flash_init());
//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     ESP_ERROR_CHECK(esp_wifi_init(&cfg));
//     ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
//     wifi_config_t wifi_config = {
//         .sta = {
//             .ssid = WIFI_SSID,
//             .password = WIFI_PASS,
//         },
//     };
//     ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
//     ESP_ERROR_CHECK(esp_wifi_start());
//     ESP_ERROR_CHECK(esp_wifi_connect());
//     ESP_LOGI(TAG, "Conectando ao Wi-Fi...");
// }

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
