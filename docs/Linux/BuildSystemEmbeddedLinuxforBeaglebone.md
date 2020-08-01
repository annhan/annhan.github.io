Trong phần hướng dẫn này sẽ hướng dẫn cách xậy dựng một hệ thống nhúng Linux trên một Kit được sử dụng phổ biến hiện nay là BeagleBone Black.

Các công việc cần thực hiện:

- Cài đặt toolchain để build các thành phần của embedded Linux.
- Build bootloader, cách định dạng thẻ nhớ để write bootloader.
- Build kernel.
- Build root filesystem.
- Tiến hành test.
Embedded Linux gồm 4 thành phần chính là:

- Toolchain: gồm một số công cụ để tạo ra code cho board.
- Bootloader: Khởi tạo hệ thống và load kernel vào bộ nhớ.
- Kernel: quản lý tài nguyên và tương tác với hardware.
- Root filesystem: chứa thư viện và các chương trình khởi chạy khi kernel hoàn thành việc khởi tạo.

1/ Install toolchain
------------

Toolchain có rất nhiều loại và chúng có ưu nhược điểm khác nhau. Chẳng hạn như các toolchain build sẵn thì chúng ta sẽ cài đặt và sử dụng chúng một cách nhanh chóng nhưng lại giới hạn trong việc tùy chỉnh cấu hình. Còn toolchain mà cần phải build mới sử dụng được thì sẽ mất thời gian và đòi hỏi có kiến thức để build nhưng chúng ta có thể dễ dàng tùy chỉnh cấu hình, ví dụ như crosstool-NG.

Để hướng dẫn nhanh chóng, bài này sẽ sử dụng toolchain build sẵn.

Để cài đặt toolchain:

```$ sudo apt install gcc-arm-linux-gnueabihf```

Câu lệnh trên sẽ cài đặt toolchain để chúng ta có thể build các thành phần khác. Các lệnh của toolchain này nằm trong thư mục /usr/bin (điều này sẽ cần thiết cho việc build root filesystem).

Tạo alias thuận tiện cho việc build. Chúng ta sẽ thường lặp lại việc gõ lệnh này, nên việc tạo alias là một cách để giúp chúng ta tối ưu hóa công việc hơn.

```$ alias armmake='make -j4 ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- '```

- ```-j4```: chỉ ra số lõi sử dụng cho việc build.
- ARCH=arm: chỉ định kiến trúc build là arm.
- CROSS_COMPILE=arm-linux-gnueabihf-: prefix toolchain
Kết thúc phần cài đặt toolchain.

2/ Build bootloader
--------

Bootloader là thành phần thứ hai của embedded Linux. Nó có nhiệm vụ khởi tạo hệ thống và loader kernel vào bộ nhớ. Cũng như toolchain, bootloader có rất nhiều loại phù hợp cho từng loại kiến trúc khác nhau. Trong phần hướng dẫn này sẽ sử dụng U-Boot cho kit BeagleBone Black.

Trở về thư mục home của user:

```$ cd```

Tiến hành get resource u-boot về:

```$ git clone git://git.denx.de/u-boot.git```

Việc get này nhanh hay chậm tùy vào tốc độ đường truyền internet.

Sau khi đã get xong, home directory sẽ có một thư mục mang tên u-boot.

```$ cd u-boot```

```$ armmake distclean```

Câu lệnh trên để clean các kết quả và cấu hình của lần build trước. Chúng ta tiến hành cấu hình u-boot cho boar:

```$ armmake am335x_evm_defconfig```

Tiến hành build bootloader:

```$ armmake```

Sau khi build xong chúng ta sẽ được file MLO và u-boot.img.

Test u-boot trên board BBB.

Trước tiên chúng ta cần write u-boot xuống SD card. Chúng ta cần định dạng SD card để thực hiện việc test.

Trong bài hướng dẫn này sử dụng Adapter microSD (loại khay nhỏ cắm trực tiếp vào máy tính). Kiểm tra thẻ nhớ đã được mount hay chưa?

```$ lsblk```

Nếu kết quả có chứa mmcblk0 thì thẻ nhớ đã được mount thành công. Tiến hành phân vùng thẻ nhớ.

Chúng ta sẽ sử dụng một script trong sách để định dạng thẻ nhớ.

Get script này về máy:

```$ git clone https://github.com/PacktPublishing/Mastering-Embedded-Linux-Programming-Second-Edition.git```

Chúng ta sẽ được file có tên “Mastering-Embedded-Linux-Programming-Second-Edition”.

Thay đổi file mode cho script:

```$ sudo chmod 755 ./Mastering-Embedded-Linux-Programming-Second-Edition/format-sdcard.sh```

Tiến hành format với lệnh:

```$ ./Mastering-Embedded-Linux-Programming-Second-Edition/format-sdcard.sh mmcblk0```

Rút thẻ nhớ và cắm vào lại để sử dụng. Tiếp theo là copy các file vào phân vùng boot.

```$ cp MLO u-boot.img /media/user_name/boot```

Chuẩn bị boot:

Board BBB chưa cấp điện, lắp thẻ nhớ vào và kết nối cổng terminal trên BBB vào thiết bị UART-to-COM được cắm vào máy tính. Sử dụng terminal console để tương tác, ở đây sử dụng picocom.

```$ sudo picocom -b 115200 /dev/ttyUSB0```

Nhấn giữ nút boot và cấp nguồn cho board, lúc này trên console sẽ hiện các message, khi có thông báo nhấn SPACE để hủy việc boot tự động ta nhấn SPACE. Lúc này chúng ta có thể tương tác với u-boot. Như vậy là u-boot đã được build thành công.

3/ Build kernel
-----------

Kernel là thành phần tiếp theo mà chúng ta sẽ làm việc. Để có thể build kernel, trước tiên chúng ta cần get resouce về máy:

```$ cd```

```$ git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git```

```$ cd linux-stable```

Xem danh sách version kernel:

```$ git branch -a```

Chọn version kernel để build:

```$ git checkout linux-4.9.y```

Bắt đàu quá trình build

```$ armmake distclean```

```$ armmake multi_v7_defconfig```

```$ armmake```

Thời gian build nhanh hay lâu tùy thuộc vào cấu hình máy. Sau khi build ta sẽ được file kết quả trong arch/arm/boot/zImage và arch/arm/boot/dts/am335x-boneblack.dtb
Copy các file này vào phân vùng boot trên thẻ nhớ

```$ cd```

```$ cd linux-statble```

```$ cp arch/arm/boot/zImage arch/arm/boot/am335x-boneblack.dtb /media/user/boot```

Test kernel thồi:

Làm tương tự với u-boot, đến khi nhấn SPACE.

=> mmc rescan

=> fatload mmc 0:1 ${loadaddr} zImage

=> fatload mmc 0:1 ${fdtaddr} am335x-boneblack.dtb
=> setenv bootargs console=ttyO0

=> bootz ${loadaddr} – ${fdtaddr}

Nếu board có thể load được kernel thì chúng ta đã build kernel thành công. Sau đó, trên console sẽ báo kernel panic. Lỗi này do chúng ta chưa có root filesystem.

4/ Build root filesystem
--------
Bước gần như cuối cùng để trong việc build. Chúng ta tiến hành get root filesystem về máy.

```$ cd```

```$ git clone git://git.buildroot.net/buildroot```

```$ cd buildroot```

Cấu hình buildroot để build root filesystem cho BBB:

```$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- distclean```

```$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- beaglebone_defconfig```

```$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig```

Sau câu lệnh trên, một cửa sổ cấu hình sẽ hiện ra. Lần lượt, chúng ta cấu hình như sau (nhấn SPACE bỏ chọn, nhấn y để chọn):

- Uncheck kernel
- Uncheck bootloader
- Target option:
    - Floating point strategy (NEON)
    - ARM instruction set (Thumb2)
- Target packages:
    - Networking application:
        [*] dhcpcd
        [*] openssh
Exit và save cấu hình lại.

Tiến hành build với lệnh:

```$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-```

Việc build sẽ khá mất thời gian. Sau khi build xong, chúng ta sẽ có được file rootfs.ext4
Tiến hành write nó xuống thẻ nhớ:

```$ sudo dd if=output/images/rootfs.ext4 of=/dev/mmcblk0p2```

Bây giờ, chúng ta sẽ cùng test thành quả.

Chúng ta cũng tiến hành boot như với u-boot đến đoạn nhấn SPACE.

Việc boot này theo các thủ công, sau khi đã chắc chắn chúng ta sẽ tạo một file để board tự boot.

=> mmc rescan

=> fatload mmc 0:1 ${loadaddr} zImage

=> fatload mmc 0:1 ${fdtaddr} am335x-boneblack.dtb
=> setenv bootargs console=${console} {optargs} root=/dev/mmcblk0p2 rootfstype=ext4

=> bootz ${loadaddr} – ${fdtaddr}

Nếu một việc suông sẽ, console sẽ xuất hiện thông báo login. Chúng ta sẽ login vào với id là “root” mà không cần mật khẩu, chúng ta có thể đổi mật khẩu sau.

Nếu muốn board tự boot, chúng ta sẽ tạo ra ra một file có tên là uEnv.txt chứa nội dung của các bước boot thủ công, nội dung file như sau:

```
bootdir=                                                         
bootfile=zImage 
fdtfile=am335x-boneblack.dtb
loadfdt=fatload mmc 0:1 ${fdtaddr} ${fdtfile}
loaduimage=fatload mmc 0:1 ${loadaddr} ${bootfile}     
uenvcmd=mmc rescan; run loaduimage; run loadfdt; run fdtboot
fdtboot=run mmc_args; bootz ${loadaddr} - ${fdtaddr}
mmc_args=setenv bootargs console=${console} ${optargs} root=/dev/mmcblk0p2 rootfstype=ext4
```
Như vậy là chúng ta đã xây dựng thành công hệ thống embedded Linux cơ bản trên board BBB

**Nguồn**: https://anhgiau.wordpress.com/2018/03/18/build-system-embedded-linux-for-beaglebone-black/comment-page-1/#comment-239