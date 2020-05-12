Config CHroot : /dev/chroot/labview chỉnh file fstab
fstab chỉ mount lúc khởi động chương trình, trong quá trình hoạt động nếu rút ra cắm lại thì sẽ mất ổ đĩa USB.









HOW
Step 1 -Set root password
sudo passwd root

Step 2 - allow root login
just go to /etc/ssh/sshd_config change the line as below
PermitRootLogin yes #(i just added this to the bottom of the file)

WHY!?!!?
What about security! This is a hobby learning pi, not a secure pi, only login as root as needed not to upset system files.

I want to edit text pi files on winscp from a PC; sometimes that means root access needed to edit - darkice.cfg for example. It's a long file, easier to copy-paste from backups or otherwise.


LINX can run voi super

cd /srv/chroot/labview
sudo schroot --run-session -c lv


--bind

/media/usb/Music /home/pi/Music none bind 0 0

USBMOUNT trong Raspberry4 bi loi -> fix

```
sudo nano /lib/systemd/system/systemd-udevd.service

Before: PrivateMounts=yes

After: PrivateMounts=no
```