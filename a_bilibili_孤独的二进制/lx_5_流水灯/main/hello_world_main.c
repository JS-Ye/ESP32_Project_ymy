// https://www.bilibili.com/video/BV1nR4y1o7VE/?spm_id_from=333.788&vd_source=feaa4fe956b0fb77bc2c5b9214217fd6

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"

#include "driver/gpio.h"

// 使用define不会占用内存，也方便开发者修改参数
#define LED_PIN GPIO_NUM_2 // GPIO_NUM
#define DELAY_MS 1000      // delay

// 使用变量的形式会占用内存空间
uint32_t status = 0;

void Led_Init(void)
{
    gpio_reset_pin(LED_PIN);                       // 选择 IO
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT); // 设置灯 IO 为输出模式
}

void app_main(void)
{
    Led_Init(); // LED初始化

    while (1)
    {
        status = !status;
        gpio_set_level(LED_PIN, status);
        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
    }
}
