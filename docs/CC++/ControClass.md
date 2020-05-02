---
layout: default
title: 
---

- Xử dụng con trỏ phải khai báo, nếu chưa dùng thì nên khai báo NULL cho con tro.

```
class Box
{
   public:
      // phan dinh nghia Constructor
      Box(double dai=1.0, double rong=1.0, double cao=1.0)
      {
         cout <<"Constructor duoc goi." << endl;
         chieudai = dai;
         chieurong = rong;
         chieucao = cao;
      }
      double theTich()
      {
         return chieudai * chieurong * chieucao;
      }
   private:
      double chieudai;     // chieu dai cua mot box
      double chieurong;    // chieu rong cua mot box
      double chieucao;     // chieu cao cua mot box
};

```
Ta khai báo con trỏ ```Box *controBox; ``` nếu chưa dùng ta nên khai báo con trỏ là NULL ```controBox = NULL```
