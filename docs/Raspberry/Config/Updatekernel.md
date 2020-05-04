---
layout: default
title: 
---

* Để update kernel lên bản mới nhất (dùng lệnh này sẽ update lên bản đang hoạt động beta nhiều lúc sẽ gây ra lỗi) 

```sudo rpi-update ```

* Để đưa kernel về lại bản stable mới nhất ( có thể khác với ver khi ta updat) 
```
sudo apt update
sudo apt install --reinstall raspberrypi-bootloader raspberrypi-kernel
```