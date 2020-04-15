---
layout: default
title: 
---

Kiểu liệt kê là một trong số các kiểu dữ liệu do người lập trình tự định nghĩa.  

kiểu liệt kê có tác dụng giúp thay thế các con số (giá trị cụ thể) bằng những cái tên có ý nghĩa, và nó còn giúp chúng ta tập hợp các giá trị có ý nghĩa liên quan với nhau thành từng nhóm. Mỗi nhóm hằng số này khi đưa vào kiểu liệt kê sẽ trở thành một kiểu dữ liệu (người ta thường gọi enumeration là một kiểu dữ liệu trong C++ vì nó có cách khai báo tương tự như khai báo biến, chứ mình thấy nó giống một group của các giá trị hơn).

Cú pháp khai báo kiểu liệt kê

Để định nghĩa một kiểu liệt kê mới, chúng ta sử dụng từ khóa enum theo cấu trúc sau:

```
enum <name_of_enumeration>
{
  //list all of values inside this block
  //each enumerator is separated by a comma, not a semicolon
};
```

VD:

```
enum Color
{
    COLOR_BLACK,
    COLOR_RED, 
    COLOR_BLUE, 
    COLOR_GREEN, 
    COLOR_WHITE,
    COLOR_CYAN,
    COLOR_YELLOW
};
```

Color backgroundColor;
Khi không gán giá trị thì giá trị của

```COLOR_BLACK =0,COLOR_RED=1```
Giá trị của phần từ sau sẽ được tăng lên 1

```
enum Direction
{
  UP = 1,   //assigned 1 by programmer
  DOWN = 3, //assigned 3 by programmer
  LEFT,     //assigned 4 by compiler
  RIGHT     //assigned 5 by compiler
};
```
Cách dùng và gán giá trị

```Color backgroundColor = COLOR_GREEN;```

Giá trị enum thường dùng trong switch...case

```
enum BossState
{
  IDLING,
  RUNNING,
  JUMPING,
  DYING
};

BossState state;

void initBoss()
{
  //init something
  state = IDLING;
}

void attack()
{
  //............
}

void activated()  
{
  //............
}

void updateAnimation(BossState state)  
{
  switch(state)
  {
  case IDLING:
    standStill();
    break;
    
  case RUNNING:
    setRunningAnimation();
    break;
    
  case JUMPING:
    setJumpingAnimation();
    break;
    
  case DYING:
    setDyingAnimation();
    break;
    
  default;
    break;
  }
}```