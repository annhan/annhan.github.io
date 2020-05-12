Create a Minimal Configuration File

# pico /var/lxc/guests/test/config

Enter the following:

lxc.utsname = test

lxc.tty = 2

lxc.rootfs = /var/lxc/guests/test/fs

Create the Container

lxc-create -f /var/lxc/guests/test/config -n test

Test the Container

# lxc-start -n test -d

[wait for a while, a few minutes]

# lxc-console -n test -t 1