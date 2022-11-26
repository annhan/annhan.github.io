---
layout: default
title: 
---

Bit Field là cách biểu diễn các thành phần dữ liệu của struct một cách tối ưu bộ nhớ.

VD:
Trong struct ta có các biến: ngày, tháng năm
Vì ngày chỉ có giới hạn 0-31 , tháng từ 1-12 và năm
Nếu ta khai báo struct bình thường choh 3 biến này sẽ chiếm tổng 12bytes.
Ngược lại khi có giới hạn các số ta nên khai báo bit field cho từng biến để giảm số bytes cấp phát trong chương trình.

```c
#include "stdio.h"
#include "conio.h"
 
struct st_day
{
    unsigned int date; 
    unsigned int month; 
    unsigned int year; 
};
struct bf_day
{
    unsigned int date : 5;  // date từ 0-31 nên chỉ cần 5 bits để biểu diễn
    unsigned int month : 4;  //month từ 1-12 nên chỉ cần 4 bits để biểu diễn
    unsigned int year : 12;  //month từ 0-4000 nên chỉ cần 12 bits để biểu diễn
};
 
void main()
{
    st_day x;
    bf_day y;
    printf("\nSize of no bit field struct: %d",sizeof(x));
    printf("\nSize of bit field struct: %d", sizeof(y));
    getch();
}
```

Kết quả:

Size of no bit field struct: 12 (3 biến unsigned int)

Size of bit field struct: 4 (chỉ cần 1 unsigned int (32bit))
