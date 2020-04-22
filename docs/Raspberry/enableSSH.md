---
layout: default
title: 
---
Vấn đề:
-------------

- Khi mới nạp image cho raspberry, nếu không có màn hình thì ta không thể login vào raspberry bằng putty được vì mặc định ssh là disable.

Giải Quyết:
-----------

- Để giải quyết vấn đề này ta cần tạo 1 file trống tên là ssh và lưu file này vào thư mục chính của thẻ SD chưa image của raspberry.

- Khi khởi động raspberry nếu thấy file này sẽ enable ssh.