---
layout: default
title: 
---

1. __main__ 
```
def main():
    mqttClient = Test()
    mqttClient.start()
if __name__ == '__main__':
    main()
```
VD lưu file thành tên file.py
Khi ta khai báo hàm ```__main__``` như vậy thì hàm main() chỉ được chạy khi ta gọi lệnh trực tiếp chạy.

VD: python file.py thì tên ```__main___``` sẽ là  ```___main___``` và thực thi hàm main.