
1. Setup access function outside of the labview chroot [ChrootAccessOutside](ChrootAccessOutside.md)

2.  Use the following code to mount the SD card in the LabVIEW chroot at the start of your program:

![image1]( image/mountSDcard.png)

3. You can now access the SD card using standard LabVIEW IO palette. For example:
![image2]( image/editSDcardfile.png)

NEW:
---------
Vi Chay EXEC VI trong LABVIEW laf da chay trong moi truong CHROOT nen ta cos the bo qua buoc 1 vaf chi can

```mount /dev/sd%s1 %s``` thay cho ```ssh root@localhost schroot -c lv -r -- mount /dev/sd%s1 %s```