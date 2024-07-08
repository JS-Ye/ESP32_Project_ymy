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

static const char *TAG = "NVS_LOG";

char *nvs_name_space = "nvs_name";
nvs_handle_t my_handle;

void app_main()
{
    // 初始化NVS的默认分区
    esp_err_t err = nvs_flash_init();
    // 如果 nvs flash 满了就清空
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase()); // 如果分区已初始化，该函数首先将其取消初始化。之后，该分区必须再次初始化才能使用。
        // 重新初始化NVS
        err = nvs_flash_init();
    }

    // 打开,类似数据库的表
    err = nvs_open(nvs_name_space, NVS_READWRITE, &my_handle); // 命名空间名称，读写模式，nvs句柄

    // 创建存储wifi账号密码的结构体，类
    typedef struct
    {
        char ssid[50];     // 50字节
        char password[50]; // 50字节
    } ap_t;

    // 写
    uint32_t max_ap = 2; // 创建可以存放两个AP的数组
    ap_t ap_set[max_ap];
    for (size_t i = 0; i < max_ap; i++)
    {
        if (i == 0)
        {
            strcpy(ap_set[i].ssid, "hiwifi");
            strcpy(ap_set[i].password, "1234567890");
        }
        if (i == 1)
        {
            strcpy(ap_set[i].ssid, "WT");
            strcpy(ap_set[i].password, "WT12345678");
        }
    }
    nvs_set_blob(my_handle, "abc", ap_set, sizeof(ap_set)); // 100字节

    // 读
    ap_t ap_get[max_ap];
    size_t lenght = sizeof(ap_get);
    nvs_get_blob(my_handle, "abc", ap_get, &lenght); // 100字节
    for (int i = 0; i < max_ap; i++)
    {
        ESP_LOGI(TAG, "ssid : password == %s : %s", ap_set[i].ssid, ap_set[i].password);
    }

    // 提交，写完文件之后必须提交才能写入NVS，相当于保存文件
    err = nvs_commit(my_handle);
    if (err != ESP_OK)
        ESP_LOGE(TAG, "nvs_commit Error");

    // 关闭NVS
    nvs_close(my_handle);

    // 反初始化NVS
    nvs_flash_deinit();
}
