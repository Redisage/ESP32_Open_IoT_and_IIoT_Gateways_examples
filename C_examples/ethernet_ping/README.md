# Ethernet ping example for ESP32 Open IoT and IIoT Gateway

## How 2 use?
1. Add your .vscode folder to the project folder (`F1` + `ESP-IDF: Add vscode Configuration Folder`).
2. Build, flash and monitor your project (`F1` + `ESP-IDF: Build, Flash and Start a Monitor on your Device`).

## Notes
* This project was made on ESP-IDF v5.2 version.
* See `sdkconfig.defaults` for required pins configuration.
* Remember to connect your CGE2 to the WLAN via Ethernet port.
* This example is based on:
    * https://github.com/espressif/esp-idf/tree/v5.2.2/examples/ethernet/basic

## Example output

```bash
I (394) eth_example: Ethernet Started
I (3934) eth_example: Ethernet Link Up
I (3934) eth_example: Ethernet HW Addr 30:ae:a4:c6:87:5b
I (5864) esp_netif_handlers: eth ip: 192.168.2.151, mask: 255.255.255.0, gw: 192.168.2.2
I (5864) eth_example: Ethernet Got IP Address
I (5864) eth_example: ~~~~~~~~~~~
I (5864) eth_example: ETHIP:192.168.2.151
I (5874) eth_example: ETHMASK:255.255.255.0
I (5874) eth_example: ETHGW:192.168.2.2
I (5884) eth_example: ~~~~~~~~~~~
```

Now you can ping your CGE2 in the terminal by entering `ping 192.168.2.151` (it depends on the actual IP address you get).

## Sources
* Manufacturer's website: https://redisage.com/
* Products link: https://redisage.com/pol_m_PAC-IoT-173.html?filter_traits%5B163%5D=164&filter_traits%5B196%5D=&filter_traits%5B38%5D=
* Contact us: support@redisage.com
