// https://www.bilibili.com/video/BV1kd4y1t7on/?spm_id_from=333.880.my_history.page.click&vd_source=feaa4fe956b0fb77bc2c5b9214217fd6

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"

#include "esp_log.h"       // ESP_LOGE();  红色标签
#include "esp_system.h"    // 系统
#include "esp_flash.h"     // menuconfig Flash
#include "esp_spi_flash.h" // SPI Flash(内存映射)

const char *hw = "硬件";
const char *sw = "软件";

void app_main(void)
{
    ESP_LOGE(sw, "IDF 版本号：%s", esp_get_idf_version());

    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    ESP_LOGE(hw, "CPU 核心数：%d", chip_info.cores);
    ESP_LOGE(hw, "CPU 版本号：%d", chip_info.revision);
    // 结构体类型
    // typedef struct
    // {
    //     esp_chip_model_t model; //!< chip model, one of esp_chip_model_t         // ESP 类型
    //     uint32_t features;      //!< bit mask of CHIP_FEATURE_x feature flags    // ESP 特征值
    //     uint8_t cores;          //!< number of CPU cores                         // CPU 核心数
    //     uint8_t revision;       //!< chip revision number                        // CPU 版本号
    // } esp_chip_info_t;

    ESP_LOGE(hw, "ESP 类型：%d", chip_info.model);
    // ESP 类型优化打印
    char *esp_type;
    switch (chip_info.model)
    {
    case CHIP_ESP32:
        esp_type = "ESP32";
        break;
    case CHIP_ESP32S2:
        esp_type = "ESP32-S2";
        break;
    case CHIP_ESP32S3:
        esp_type = "ESP32-S3";
        break;
    case CHIP_ESP32C3:
        esp_type = "ESP32-C3";
        break;
    case CHIP_ESP32H2:
        esp_type = "ESP32-H2";
        break;
    default:
        esp_type = "Unknown";
        break;
    }
    ESP_LOGE(hw, "ESP 类型：%s", esp_type);
    // 枚举类型
    // typedef enum
    // {
    //     CHIP_ESP32 = 1,   //!< ESP32
    //     CHIP_ESP32S2 = 2, //!< ESP32-S2
    //     CHIP_ESP32S3 = 9, //!< ESP32-S3
    //     CHIP_ESP32C3 = 5, //!< ESP32-C3
    //     CHIP_ESP32H2 = 6, //!< ESP32-H2
    // } esp_chip_model_t;

    ESP_LOGE(hw, "ESP 特征值:     %d", chip_info.features); // 0011 0010 = 50
    ESP_LOGE(hw, "内置 Flash:     %s", chip_info.features & CHIP_FEATURE_EMB_FLASH ? "Yes" : "No");
    ESP_LOGE(hw, "2.4GHz WiFi:    %s", chip_info.features & CHIP_FEATURE_WIFI_BGN ? "Yes" : "No");
    ESP_LOGE(hw, "BLE 蓝牙低功耗: %s", chip_info.features & CHIP_FEATURE_BLE ? "Yes" : "No");
    ESP_LOGE(hw, "BT 金典蓝牙:    %s", chip_info.features & CHIP_FEATURE_BT ? "Yes" : "No");
    ESP_LOGE(hw, "IEEE 802.15.4:  %s", chip_info.features & CHIP_FEATURE_IEEE802154 ? "Yes" : "No");
    ESP_LOGE(hw, "内置 PSRAM:     %s", chip_info.features & CHIP_FEATURE_EMB_PSRAM ? "Yes" : "No");
    // #define CHIP_FEATURE_EMB_FLASH BIT    (0)                 //!< 内置flash
    // #define CHIP_FEATURE_WIFI_BGN BIT     (1)                 //!< 2.4GHz WiFi
    // #define CHIP_FEATURE_BLE BIT          (4)                 //!< BLE 蓝牙低功耗
    // #define CHIP_FEATURE_BT BIT           (5)                 //!< BT 金典蓝牙
    // #define CHIP_FEATURE_IEEE802154 BIT   (6)                 //!< IEEE 802.15.4
    // #define CHIP_FEATURE_EMB_PSRAM BIT    (7)                 //!< 内置psram

    // ESP_LOGE(hw, "ESP-Flash: %d", esp_flash_get_chip_size());
    ESP_LOGE(hw, "ESP-menuconfig-Flash: %d MBytes", spi_flash_get_chip_size() / (1024 * 1024));
    ESP_LOGE(hw, "ESP-menuconfig-Flash: %d MBits", (spi_flash_get_chip_size() * 8) / (1024 * 1024));

    // 获取芯片mac地址，建议将mac地址存入数组中
    // uint8_t mac_address;
    // esp_efuse_mac_get_default(&mac_address);
    // ESP_LOGE(hw, "Mac Address: %02X-%02X-%02X-%02X-%02X-%02X", *(&mac_address + 0), *(&mac_address + 1), *(&mac_address + 2), *(&mac_address + 3), *(&mac_address + 4), *(&mac_address + 5));
    uint8_t mac_address[6];                  // 数组
    esp_efuse_mac_get_default(&mac_address); // 获取mac地址存入mac_address2[6]数组中
    ESP_LOGE(hw, "Mac Address: %02X-%02X-%02X-%02X-%02X-%02X", mac_address[0], mac_address[1], mac_address[2], mac_address[3], mac_address[4], mac_address[5]);
}
