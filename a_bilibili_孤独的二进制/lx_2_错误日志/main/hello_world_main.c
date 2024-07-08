// https://www.bilibili.com/video/BV1KG4y1d7Ed/?vd_source=feaa4fe956b0fb77bc2c5b9214217fd6

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"

#include "esp_log.h" // ESP_LOGE();

const char *tagTraffic = "交通灯";
bool secretLog = true; // 当secretLog为真，D,V 的日志就会被打印出来

// E,W,I 是给用户看的
// D,V 是给程序员看的
void app_main(void)
{
    if (secretLog == true)
    {
        esp_log_level_set(tagTraffic, ESP_LOG_VERBOSE); // 设置指定标签tagTraffic的日志级别
    }
    // E error，错误信息
    ESP_LOGE(tagTraffic, "不亮了");
    // W Warning，警告信息
    ESP_LOGW(tagTraffic, "灯泡寿命还有5%%");
    // I Information，更多信息
    ESP_LOGI(tagTraffic, "灯泡寿命还有75%%");

    // D Debug，排错信息
    ESP_LOGD(tagTraffic, "灯泡亮度1000, 已使用200小时");
    // V Version，更多的排错信息
    ESP_LOGV(tagTraffic, "灯丝还有5丝厚度, 氧化程度0.23, 寿命正常");
    // 需要设置, 如果不设置，程序员看的 D,V 就不能打印出来：idf.py menuconfig → Component config → Log output → Maximum log verbosity (Verbose)
}

// E,W,I 是给用户看的
// D,V 是给程序员看的
// void app_main(void)
// {
//     if (secretLog == true)
//     {
//         esp_log_level_set(tagTraffic, ESP_LOG_VERBOSE);
//     }
//     // E error，错误信息
//     ESP_LOGE("交通灯", "不亮了");
//     // W Warning，警告信息
//     ESP_LOGW("交通灯", "灯泡寿命还有5%%");
//     // I Information，更多信息
//     ESP_LOGI("交通灯", "灯泡寿命还有75%%");

//     // D Debug，排错信息
//     ESP_LOGD("交通灯", "灯泡亮度1000, 已使用200小时");
//     // V Version，更多的排错信息
//     ESP_LOGV("交通灯", "灯丝还有5丝厚度, 氧化程度0.23, 寿命正常");
//     // 需要设置, 如果不设置，程序员看的 D,V 就不能打印出来：idf.py menuconfig → Component config → Log output → Default log verbosity (Verbose)
// }
