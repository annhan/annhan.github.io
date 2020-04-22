---
layout: default
title: 
---
Chỉnh sữa ```sudo nano /etc/dhcpcd.conf```

add thêm dòng cuối ```nohook lookup-hostname```


Phần này còn thiếu sót sẽ bổ xung sau.
---------------

Python
---------------
Có thể cài đặt ip static nhanh chóng trong lần chạy, khi reset là hết bằng dòng lệnh

``` 
    import os   
    os.system('sudo ifconfig eth0 down')
    os.system('sudo ifconfig eth0 192.168.1.10')
    os.system('sudo ifconfig eth0 up')
```
