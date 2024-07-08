// https://zhuanlan.zhihu.com/p/609327156
// NVS 的读写删除

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "esp_log.h"

#include "nvs_flash.h"

static const char *TAG = "NVS_LOG";

char *nvs_name_space = "nvs_name";
nvs_handle_t my_handle;

int8_t nvs_i8_value = 0;
int16_t nvs_i16_value = 0;
uint32_t nvs_u32_value = 0;
uint64_t nvs_u64_value = 0;
char *nvs_i8_key = "nvs_i8";
char *nvs_i16_key = "nvs_i16";
char *nvs_u32_key = "nvs_u32";
char *nvs_u64_key = "nvs_u64";

char *str_key = "nvs_str";
char str_value[100] = "hello_nvs";
uint32_t len = 100;

void app_main()
{
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    ESP_LOGI(TAG, "start line %d", __LINE__); // 打印行号

    // 初始化NVS的默认分区
    esp_err_t err = nvs_flash_init();
    // 如果 nvs flash 满了就清空
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        // 擦除"nvs"的默认分区
        ESP_ERROR_CHECK(nvs_flash_erase()); // 如果分区已初始化，该函数首先将其取消初始化。之后，该分区必须再次初始化才能使用。
        // 重新初始化NVS
        err = nvs_flash_init();
    }

    // 打开,类似数据库的表
    err = nvs_open(nvs_name_space, NVS_READWRITE, &my_handle); // 命名空间名称，读写模式，nvs句柄

    // 读写
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "opening NVS Error (%s)!\n", esp_err_to_name(err));
    }
    else
    {
        ESP_LOGI(TAG, "NVS open OK");

        // 读取，类似数据读字段对应的值
        // 整数类型
        err = nvs_get_i8(my_handle, nvs_i8_key, &nvs_i8_value); // nvs_get_i8(nvs句柄, key, value);
        if (err == ESP_OK)
            ESP_LOGI(TAG, "key:value == %s : %d\n", nvs_i8_key, nvs_i8_value);
        else
            ESP_LOGE(TAG, "key:value == %s : %d", nvs_i8_key, nvs_i8_value);
        err = nvs_get_i16(my_handle, nvs_i16_key, &nvs_i16_value);
        if (err == ESP_OK)
            ESP_LOGI(TAG, "key:value == %s : %d\n", nvs_i16_key, nvs_i16_value);
        else
            ESP_LOGE(TAG, "key:value == %s : %d", nvs_i16_key, nvs_i16_value);
        err = nvs_get_u32(my_handle, nvs_u32_key, &nvs_u32_value);
        if (err == ESP_OK)
            ESP_LOGI(TAG, "key:value == %s : %d\n", nvs_u32_key, nvs_u32_value);
        else
            ESP_LOGE(TAG, "key:value == %s : %d", nvs_u32_key, nvs_u32_value);
        err = nvs_get_u64(my_handle, nvs_u64_key, &nvs_u64_value);
        if (err == ESP_OK)
            ESP_LOGI(TAG, "key:value == %s : %llu\n", nvs_u64_key, nvs_u64_value);
        else
            ESP_LOGE(TAG, "key:value == %s : %llu", nvs_u64_key, nvs_u64_value);
        // 字符串类型
        err = nvs_get_str(my_handle, str_key, str_value, &len); // 自定义100是读取最大长度
        if (err == ESP_OK)
            ESP_LOGI(TAG, "key:value == %s : %s\n", str_key, str_value);
        else
            // 当NVS为空值或0时，则打印下面信息
            ESP_LOGE(TAG, "key:value == %s : %s", str_key, str_value);

        // 修改字段的值
        // 写数值
        nvs_i8_value += 1;
        nvs_i16_value += 1;
        nvs_u32_value += 1;
        nvs_u64_value += 1;
        err = nvs_set_i8(my_handle, "nvs_i8", nvs_i8_value); // nvs_set_i8(nvs句柄, key, value);
        if (err != ESP_OK)
            ESP_LOGE(TAG, "nvs_i8 Error");
        err = nvs_set_i16(my_handle, "nvs_i16", nvs_i16_value);
        if (err != ESP_OK)
            ESP_LOGE(TAG, "nvs_i16 Error");
        err = nvs_set_u32(my_handle, "nvs_u32", nvs_u32_value);
        if (err != ESP_OK)
            ESP_LOGE(TAG, "nvs_u32 Error");
        err = nvs_set_u64(my_handle, "nvs_u64", nvs_u64_value);
        if (err != ESP_OK)
            ESP_LOGE(TAG, "nvs_u64 Error");
        // 写字符串
        sprintf(str_value, "hello_nvs_%llu", nvs_u64_value);
        err = nvs_set_str(my_handle, str_key, str_value);

        // 提交，写完文件之后必须提交才能写入NVS，相当于保存文件
        err = nvs_commit(my_handle);
        if (err != ESP_OK)
            ESP_LOGE(TAG, "nvs_commit Error");

        // 关闭NVS
        nvs_close(my_handle);

        // 复位查看值
        for (int i = 10; i >= 0; i--)
        {
            printf("Restarting in %d seconds...\n", i);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        esp_restart(); // esp重启
    }
}