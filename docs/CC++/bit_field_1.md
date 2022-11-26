---
layout: default
title: 
---

# Kết hợp bitfield trong union

Trong lập trình nhúng, nhiều protocol chỉ cần  vài bit trong dữ liệu. Vậy làm thế nào để tách dữ liệu trong 1byte 1 cách nhanh nhất mà không cần code.

Khi đó dựa vào đặt tính của union và bitfield ta có thể tự động nhận dữ liệu theo từng bit của data.

VD: Truyền data có độ dài bằng 8bits. Trong đó  3 bits đầu để chưa ID và 5 bits sau chứa dữ liệu.




# Khai báo

```c
MSB        LSB
 7            0
+------+-------+
| five | three |
| bits | bits  |
+------+-------+
// Khai báo bitfield trong 8 bit
struct fields_tag {
   // LSB
   unsigned int five:5;
   unsigned int three:3;
   // MSB
};

// Khai báo union chứa bitfield và 1 kiểu 8bit
typedef union some_reg_tag {
    uint8_t raw;
    struct fields_tag fields;
} some_reg_t;
```

# Sử dụng


```c

some_reg_t a_register;
a_register.raw = 0xC2;  // assign using raw field.

Serial.print("some reg = ");  // dump entire register
Serial.println(a_register.raw, HEX);   // dump register by field
Serial.print("some reg.three = ");
Serial.println(a_register.fields.three, HEX);
Serial.print("some reg.five = ");
Serial.println(a_register.fields.five, HEX);
```

# Kết quả:

```
some reg = C2
some reg.three = 6
some reg.five = 2
```

Vậy là nhờ ứng dụng bitfield và union ta có thể tự động tách hoặc gộp data trong lập trình nhúng