---
layout: default
title: 
---

Trực tiếp:

```
int a = 0;
a = 2;
```

Gián tiếp bằng tham chiếu:

```
int a = 0;
int& b = a;
b = 2; //  a == 2
```

Gián tiếp bằng con trỏ:

```
int a = 0;
int* b = &a;
*b = 2; // a == 2
```