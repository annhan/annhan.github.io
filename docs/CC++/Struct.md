---
layout: default
title: 
---

Khai báo Struct

VD1:
```
struct Books
{
   char  tieude[50];
   char  tacgia[50];
   char  chude[100];
   int   book_id;
};
```
Ta khai báo struct Books Quyeensach1; 

Khi đó ta truy cập vào bằng Quyensach1.tieude...

Con trỏ

```
struct Books* quyensach2;

quyensach2=&quyensach1;
```

khi đó ta truy vẫn phần tử: quyensach2->tieude;



Từ khóa typedef

```
typedef struct Books
{
   char  tieude[50];
   char  tacgia[50];
   char  chude[100];
   int   book_id;
}Sach;
```

khi dùng typedef ta khai báo chỉ cần

Sach Quyensach1;

truy vẫn Quyensach1.tieude;




```
struct sinhvien 
{
    char MSV[20]; // ma sinh vien
    char hoten[30]; // ho ten sinh vien
    double diemTB; // diem trung binh
    struct ngaysinh 
    {
        int ngay, thang, nam;
    } ns;
};
```
 Khai báo biến con trỏ và cấp phát bộ nhớ struct

```
struct sinhvien *CNPMK10A = (struct sinhvien*) malloc(n * sizeof(struct sinhvien)); 
```

Truy cập các phần tử struct

Truy cập các thành phần cấu trúc

Để truy cập để lấy dữ liệu các thành phần của con trỏ cấu trúc ta có 3 cách sau:
Cách 1: CNPMK10A[i].diemTB;
Cách 2: (*(CNPMK10A+i)).diemTB;
Cách 3: (CNPMK10A+i) ->diemTB;
Cả 3 cách trên đều truy cập tới DTB.
Để lấy địa chỉ ta cũng có 2 cách:
Cách 1: &CNPMK10A[i].DTB;
Cách 2: &(CNPMK10A+i)->diemTB


2.
```
#include <iostream>    
using namespace std;    
struct HinhChuNhat      
{      
   int chieuDai;
   int chieuRong;
   HinhChuNhat(int ch, int cr) {
       chieuDai = ch;
       chieuRong = cr;
   }
   void TinhDienTich() {
       cout << "Dien tich hinh chu nhat la: " << (chieuDai * chieuRong) << endl;  
   }   
};      
int main(void) {    
    struct HinhChuNhat hcn = HinhChuNhat(3,5);        
    hcn.TinhDienTich();    
    return 0;    
}
```