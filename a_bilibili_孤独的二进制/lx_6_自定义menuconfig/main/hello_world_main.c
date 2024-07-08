// https://www.bilibili.com/video/BV1S44y1D7cf/?spm_id_from=333.788&vd_source=feaa4fe956b0fb77bc2c5b9214217fd6

// 资料：
// https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/api-reference/kconfig.html#id4
// https://www.kernel.org/doc/html/latest/kbuild/kconfig-language.html#menu-structure  // 首菜单
// https://www.kernel.org/doc/html/latest/kbuild/kconfig-language.html#menu-entries    // 子菜单

// 配置：
// 首先需要在main目录下创建 Kconfig.projbuild 文件，然后添加配置项
/*
 * menu "点灯配置" //首菜单
 *
 *     config LED_GPIO_NUM  //子菜单
 *         int                         //类型
 *         prompt "LED_GPIO_NUM"       //子菜单名称
 *         range 0 39                  //可以输入范围
 *         default 2                   //默认值为GPIO2
 *         help                        //帮助
 *             "LED与开发板的连接管脚"  //帮助提示词
 *
 * endmenu
 */

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"

#include "driver/gpio.h"
#include "esp_log.h" // ESP_LOGI();

// 使用define不会占用内存，也方便开发者修改参数
#define LED_PIN CONFIG_LED_GPIO_NUM   // GPIO,默认为GPIO2
#define DELAY_MS CONFIG_DELAY_TIME_MS // Delay,默认1000ms

// 使用变量的形式会占用内存空间
uint32_t status = 0;

void Led_Init(void)
{
    gpio_reset_pin(LED_PIN);                       // 选择 IO
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT); // 设置灯 IO 为输出模式

    ESP_LOGI("blink", "GPIO: %d", LED_PIN);
    ESP_LOGI("blink", "Dalay: %dms", DELAY_MS);
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
