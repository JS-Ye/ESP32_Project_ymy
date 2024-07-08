// https://www.bilibili.com/video/BV1Y841157U8/?spm_id_from=333.788&vd_source=feaa4fe956b0fb77bc2c5b9214217fd6
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
#include "esp_err.h"

static const char *TAG = "NVS_LOG";

char *nvs_name_space = "nvs_name";
nvs_handle_t my_handle;

void app_main()
{
    // 初始化NVS的默认分区
    ESP_ERROR_CHECK(nvs_flash_init()); // 初始化nvs，当不能成功初始化nvs时，ESP_ERROR_CHECK会触发重启，然后再重新触发初始化nvs

    // 打开,类似数据库的表
    nvs_open(nvs_name_space, NVS_READWRITE, &my_handle); // 命名空间名称，读写模式，nvs句柄

    // 创建存储wifi账号密码的结构体，类
    typedef struct
    {
        char ssid[50];     // 50字节
        char password[50]; // 50字节
    } ap_t;

    // 写
    uint32_t max_ap = 20; // 创建可以存放20个AP的数组
    ap_t ap_set[max_ap];
    for (size_t i = 0; i < max_ap; i++)
    {
        strcpy(ap_set[i].ssid, "hiwifi");
        strcpy(ap_set[i].password, "1234567890");
    }
    char key[15];
    sprintf(key, "key %d", esp_random());
    esp_err_t err = nvs_set_blob(my_handle, key, ap_set, sizeof(ap_set));
    nvs_commit(my_handle); // 提交，写完文件之后必须提交才能写入NVS，相当于保存文件
    if (err == ESP_OK)
    {
        ESP_LOGE(TAG, "start line %d", __LINE__); // 打印行号
        esp_restart();                            // esp重启
    }
    else
    {
        ESP_LOGE(TAG, "nvs_commit Error  nvs_set_blob: %d", err);                  // 大概运行1~2分钟，NVS就会被写满
        ESP_LOGE(TAG, "nvs_commit Error  nvs_set_blob: %s", esp_err_to_name(err)); // 大概运行1~2分钟，NVS就会被写满
    }

    // 关闭NVS
    nvs_close(my_handle);

    // 反初始化NVS
    nvs_flash_deinit();
}
