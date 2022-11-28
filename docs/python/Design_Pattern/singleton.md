---
layout: default
title: 
---

Singleton là một mẫu thiết kế khởi tạo, đảm bảo rằng chỉ có một đối tượng cùng kiểu tồn tại và cung cấp một điểm truy cập duy nhất vào nó cho bất kỳ mã nào khác.

Ví dụ dưới ta có 2 phương thức khởi tạo Singleton.

- Class SingletonMeta giúp tạo một Singleton được bảo vệ trong khi khởi tạo trong multithreading

- Class Singleton tạo ra Singleton object nhưng nếu có multithread thì khả năng gây lỗi sẽ xảy ra.


```
#!/usr/bin/ python3
# coding: utf8

from threading import Lock
from enum import  Enum

class SingletonMeta(type):

    _instances = {}
 
    _lock: Lock = Lock()

 
    def __call__(cls, *args, **kwargs):
        with cls._lock:

            if cls not in cls._instances:
                instance = super().__call__(*args, **kwargs)
                cls._instances[cls] = instance
        return cls._instances[cls]
    
class Singleton(type):
    _instances = {}

    def __call__(cls, *args, **kwargs):
        # sourcery skip: instance-method-first-arg-name
        if cls not in cls._instances:
            cls._instances[cls] = super(Singleton, cls).__call__(*args, **kwargs)
        return cls._instances[cls]
		
class payment(object, metaclass=SingletonMeta):

    def __init__(self):
	pass
```
