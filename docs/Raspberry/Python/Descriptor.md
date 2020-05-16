VD 
```
class Programmer(object):
    def __init__(self, name, age, salary, rating):
        self.name = name
        self.age = age
        self.salary = salary
        self.rating = rating
```

Trên VD trên bên ngoài class ta có thể thay đổi trực tiếp biến name, age.

Khi ta không muốn bên ngoài thay đổi trực tiếp biến ( vì ràng buộc có lẽ tuổi sẽ >0 ..) ta sẽ dùng @property

```
class Programmer(object):
    def __init__(self, name, age, salary, rating):
        self._age = None # tạo một thuộc tính private cho age

        self.name = name
        self.age = age
        self.salary = salary
        self.rating = rating

    @property
    def age(self):
        return self._age

    @age.setter
    def age(self, value):
        if age > 0:
            self._age = value
        else:
            raise ValueError("Negative value not allowed: %s" % age)
```

Khi chay sẽ báo lỗi nếu tuổi nhập vào <0

```
>>> kiennt = Programmer('kiennt', 26, 500, 5)
>>> try:
        kiennt.age = -10
    except ValueError:
        print "Cannot set negative value"
Cannot set negative value
```