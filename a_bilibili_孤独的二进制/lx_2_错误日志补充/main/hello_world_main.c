// https://www.bilibili.com/video/BV1nR4y1o7VE/

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"

#include "esp_log.h"

static char *level1 = "test1";
static char *level2 = "test2";

static char *level3 = "test";
static char *level4 = "test";

void app_main(void)
{
    esp_log_level_set(level1, ESP_LOG_DEBUG);    // Component config → Log output → Maximum log verbosity (Debug)
    ESP_LOGD(level1, "test1 debug information"); // 只打印level1
    ESP_LOGD(level2, "test2 debug information"); // 不打印level2

    esp_log_level_set(level3, ESP_LOG_DEBUG);
    ESP_LOGD(level3, "test3 debug information"); // 既打印level3
    ESP_LOGD(level4, "test4 debug information"); // 又打印level4
    // 因为esp_log_level_set只对“test”操作，又因为 level3 和 level4 都是 “test”，也就是level3==level4，跟一下方式同理
    // esp_log_level_set("test", ESP_LOG_DEBUG);
    // ESP_LOGD("test", "test3 debug information");
    // ESP_LOGD("test", "test4 debug information");
}
