---
layout: default
title: 
---
Bước 1: tạo net class để gom các nhóm dây cần thực tiện.<br>  
Tạo net class: nhằm giúp altium hiểu những đường tín hiệu nào dùng ký thuật này.  <br>   
Để tạo net class ta vào PCB và click chuột phải chọn NEW Class.<br>   
<img src="/docs/Picture/Altium/HSP_LEN1.PNG" alt="1" > <br>   
Chọn các đường cần add vào class và đặt tên class.  <br>   
<br>   
<img src="/docs/Picture/Altium/HSP_LEN2.PNG" alt="2" > 
<br><br>   
Bước 2: Cấu hình sai số giữa các đường.<br>   
Vào Design -> Design Rules -> High Speed -> Matched Lengths -> New Rules  
<br>   

<img src="/docs/Picture/Altium/HSP_LEN3.PNG" alt="3" > <br>   
<br>   
<br>   
Bước 3: Vẽ layout  <br>   
ta cứ laout bình thường và các đường mạch trong class báo vàng là nó đã vượt qua sai số như bước 2 đã cài đặt. <br>    
Route->Interactive length Tuning -> Chonj dây sau đó click TAB để chỉnh thông số.  <br>   
<br>   
<img src="/docs/Picture/Altium/HSP_LEN4.PNG" alt="4" >   <br>   