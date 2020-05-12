
1. Setup access function outside of the labview chroot [ChrootAccessOutside](ChrootAccessOutside.md)

2.  Use the following code to mount the SD card in the LabVIEW chroot at the start of your program:

![image1]( image/mountSDcard.png)

3. You can now access the SD card using standard LabVIEW IO palette. For example:
![image2]( image/editSDcardfile.png)

NEW:
---------
Vì chạy EXEC VI trong LABVIEW là đã chạy trong môi trường root của Chroot nên ta có thể bỏ qua bước 1 và dùng lệnh trực tiesrep. Sẽ ra kết quả nhanh hơn ( 50ms thay vì 2000ms nếu dùng lệnh cũ)

```mount /dev/sd%s1 %s``` thay cho ```ssh root@localhost schroot -c lv -r -- mount /dev/sd%s1 %s```