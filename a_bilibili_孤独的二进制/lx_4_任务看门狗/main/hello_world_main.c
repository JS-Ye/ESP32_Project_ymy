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

    static char pcWriteBuffer[512] = {0}; // 定义一个char型的数组来缓存数据

    while (1)
    {
        vTaskList(pcWriteBuffer); // 将任务列表数据缓存到数组

        printf("--------------------------------------------\n");
        printf("名称           状态   优先级   堆栈    编号  \n");
        printf("--------------------------------------------\n");
        printf("%s\n", pcWriteBuffer); // 打印Task系统信息
        // Component config → FreeRTOS → Enable FreeRTOS stats formatting functions
        // Component config → FreeRTOS → Enable display of xCoreID in vTaskList (NEW)

        // ESP_LOGI("sw", "Hello FreeRTOS");

        // 如果没有加延时喂狗，会触发任务看门狗阻塞空闲任务。默认情况下如果不加延时喂狗，系统会5s触发一次看门狗。可以通过以下方式修改触发看门狗的时间：
        // Component config → ESP System Settings → (5)Task Watchdog timeout period (seconds)
        vTaskDelay(1000 / portTICK_PERIOD_MS); // sleep for 1 second
    }
}
