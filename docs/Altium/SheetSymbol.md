---
layout: default
title: 
---

<h1 style="background-color:LightGray;">Vấn đề </h1>   
  
Đôi khi một file bản vẽ quá lớn sẽ gây khó khăn cho chúng ta trong việc vẽ schematic.  
Có những khối lặp đi lặp lại nhiều lần trong schematic->gây tốn thời gian trong vẽ. 

Để giải quyết vấn đề ấy chúng ta cần chia schematic theo các khối riêng biệt, nhằm dễ bao quát, sữa chữa..  

<h1 style="background-color:LightGray;">Hướng dẫn. </h1>   

- Tạo file schematic.  
- Vào Place->Sheet Symbol để tạo 1 khối có chức năng riêng.  
- Vào Place->Sheet ENtry để tạo các chân IN/OUT hay BUS kết nối vào khối  
- Để vẽ schematic của khối ta click chuột phải vào khối chọn "Sheet Symbol Action"-> Create sheet from Sheet Symbol.  
- Khi đó altium sẽ tạo 1 file mới và ta thực hiện vẽ schematic cho khối đó.  
- Khi có nhiều khối lặp đi lặp lại ta có thể khai báo repeat khối trong phần name REPEAT(tenkhoi,1,4) Sẽ tạo 4 khối giống nhau.  
- Các chân bus cũng cần khao báo repeat(O,1,4) với O là chân lần lượt O1,O2,O3,O4 đã được khai báo trên BUS.  
- PCB: chỉ cần vẽ PCB cho 1 khối rồi update sang các khối còn lại.   
- Để update ta vào Design->Room->Copy room format sau đó chọn khối đã vẽ và chọn khối cần update.  

<img src="/docs/Picture/Altium/sheetsynbol1.png" alt="Flowers in Chania" >  
<br>  
<br>  
<img src="/docs/Picture/Altium/sheetsynbol2.png" alt="Flowers in Chania" >