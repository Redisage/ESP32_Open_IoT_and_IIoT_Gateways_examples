# WiFi example for ESP32 Open IoT and IIoT Gateway

## How 2 use?
1. Add your .vscode folder to the project folder (`F1` + `ESP-IDF: Add vscode Configuration Folder`).
2. Build, flash and monitor your project (`F1` + `ESP-IDF: Build, Flash and Start a Monitor on your Device`).

## Notes
* This project was made on ESP-IDF v5.2 version.
* Use `#define ESP_WIFI_MODE_STA 1` or `#define ESP_WIFI_MODE_AP 1` to change between WI-FI station and access point mode.
* Change WI-FI login settings in `#define ESP_WIFI_SSID "wifi_ssid"` and `#define ESP_WIFI_PASS "wifi_pass"`.
* This example is based on:
    * https://github.com/espressif/esp-idf/tree/master/examples/wifi/getting_started/station
    * https://github.com/espressif/esp-idf/tree/master/examples/wifi/getting_started/softAP

## Sources
* Manufacturer's website: https://redisage.com/
* Products link: https://redisage.com/pol_m_PAC-IoT-173.html?filter_traits%5B163%5D=164&filter_traits%5B196%5D=&filter_traits%5B38%5D=
* Contact us: support@redisage.com
