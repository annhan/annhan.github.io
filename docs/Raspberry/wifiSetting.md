---
layout: default
title: 
---
WifiSetting
---------------------
Cài Wifi cho raspberry.
SSH vào raspberry và edit ```sudo nano /etc/wpa_supplicant/wpa_supplicant.conf```
Và thêm vào các dòng này
ssid: điền tên wifi
psk: passwork của wifi

```
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1

network={
ssid="scc"
scan_ssid=1
psk="ss"
}
```