---
layout: default
title: 
---
Ba phương pháp được đề cập trong hướng dẫn này là:
•	RC.local - Có thể là cách dễ nhất và đơn giản nhất để chương trình của bạn chạy khi khởi động. Nhược điểm là các tác vụ bắt đầu với RC.local xảy ra trước khi hệ thống windows X khởi động, điều đó có nghĩa là bạn sẽ không có quyền truy cập vào các yếu tố giao diện người dùng đồ họa (GUI).
•	tự động khởi động - Được sử dụng để tự động chạy các chương trình của bạn sau khi LXDE (môi trường máy tính để bàn được sử dụng bởi Raspbian) bắt đầu. Nó hơi phức tạp hơn một chút so với RC.local, nhưng nó cho phép bạn chạy các chương trình yêu cầu các yếu tố đồ họa.
•	systemd - Cách mới và phổ biến để tự động khởi động các chương trình trong Linux. Đây chắc chắn là phức tạp nhất trong ba, nhưng nó cho phép bạn chạy trước khi LXDE bắt đầu, đợi cho đến khi bạn có quyền truy cập vào các quy trình khác (ví dụ: mạng, máy tính để bàn đồ họa) hoặc đơn giản là khởi động lại chương trình của bạn nhiều lần cho đến khi nó hoạt động. Như vậy, đây là một cách mạnh mẽ để tạo và quản lý các dịch vụ chạy trong nền.
Dùng Cách 3.

Với Gui:
Tạo một tệp .service mới trong thư mục systemd:

```
sudo nano /lib/systemd/system/clock.service
```
Nhập văn bản sau vào tài liệu:

```
[Unit]
Description=Start Clock

[Service]
Environment=DISPLAY=:0
Environment=XAUTHORITY=/home/pi/.Xauthority
ExecStart=/usr/bin/python3 /home/pi/clock.py
Restart=always
RestartSec=10s
KillMode=process
TimeoutSec=infinity

[Install]
WantedBy=graphical.target
```

Không cần Gui thi 
Tạo một tệp .service mới trong thư mục systemd:```sudo nano /lib/systemd/system/blink.service```

Nhập văn bản sau vào tài liệu:

```
[Unit]
Description=Blink my LED
After=multi-user.target

[Service]
ExecStart=/usr/bin/python3 /home/pi/blink.py

[Install]
WantedBy=multi-user.target
```

Các lệnh.
```
sudo systemctl daemon-reload

sudo systemctl enable blink.service

systemctl status clock.service

sudo systemctl stop clock.service
sudo systemctl start clock.service
```


Điều này có thể hữu ích để khởi động lại một dịch vụ nếu bạn đã thay đổi dịch vụ mà không phải khởi động lại hệ thống. Chỉ cần nhớ chạy sudo systemctl daemon-reloadnếu bạn thực hiện bất kỳ thay đổi nào đối với tệp .service!

