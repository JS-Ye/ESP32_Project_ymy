// https://www.bilibili.com/video/BV1S3411f71Z/?spm_id_from=pageDriver

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"

#include "esp_log.h"

void app_main(void)
{
    ESP_LOGI("COUNTER", "Tickc (ms) : %d", portTICK_PERIOD_MS); // 打印一个Tick有多少ms

    while (1)
    {
        ESP_LOGI("sw", "Hello FreeRTOS_1");
        // vTaskDelay(1000 / portTICK_PERIOD_MS); // sleep for 1 second

        // ESP_LOGI("sw", "Hello FreeRTOS_2");
        vTaskDelay(1000); // sleep for 1 second
        // menuconfig配置：Component config → FreeRTOS → (1000) Tick rate (Hz)
    }
}
