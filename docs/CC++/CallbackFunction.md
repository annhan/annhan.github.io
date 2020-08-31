---
layout: default
title: 
---

Khi ta viết thư viện, trong hàm sử lý dữ liệu hay có hàm ta sẽ để người dùng tự định nghĩa bên ngoài chương trình chính và chỉ truyền vào địa chỉ hàm để ta gọi khi cần dùng.


```c
#include <stdio.h>

int add_two_number(int a, int b);
int sub_two_number(int a, int b);
int call_func(int (*ptr_func)(int, int), int a, int b);

int main (int *argc, char *argv[])
{
     if (argv[1][0] == '+')
         printf("%d\n", call_func(add_two_number, 5, 9));
     else if (argv[1][1] == '-')
         printf("%d\n", call_func(sub_two_number, 5, 9));

     return 0;
}

int add_two_number(int a, int b)
{
     return a + b;
}

int sub_two_number(int a, int b)
{
     return a - b;
}

int call_func(int (*ptr_func)(int, int), int a, int b)
{
    return ptr_func(a, b);
}
```