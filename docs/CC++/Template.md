---
layout: default
title: 
---

```c
#include <iostream>
using namespace std;

template <class T>
T sum (T a, T b)
{
  T result;
  result = a + b;
  return result;
}

int main () {
  int i=5, j=6, k;
  double f=2.0, g=0.5, h;
  k=sum<int>(i,j); //sum<int> tạo ra hàm sum với kiểu dữ liệu của T là int
  h=sum<double>(f,g);//sum<double> tạo ra hàm sum với kiểu dữ liệu của T là double
  cout << k << '\n';
  cout << h << '\n';
  return 0;
}
```