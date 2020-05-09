1. Install an ssh client to your chroot:
```
sudo schroot -r -c lv
opkg update
opkg install openssh-ssh
exit
```

2. Configure pub key authentication so you don't have to type in a password interactively (Hint: This let's you use the ssh client from LabVIEW System Exec VI).
```
ssh-keygen -t rsa
stick with the defaults when it prompts you, especially when it asks for the passphrase; we want an empty passphrase
cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
sudo mkdir /srv/chroot/labview/root/.ssh
sudo cp ~/.ssh/id_rsa* /srv/chroot/labview/root/.ssh/
```
3. Now log back into the chroot and run the ssh command once so that you can add localhost to the list of known hosts
```
sudo schroot -r -c lv
ssh root@localhost ls  When prompted to add localhost to the list of known hosts, say yes
exit
```
4. At this point you can run commands from within the LV chroot in the system outside the chroot by running a command of the form ssh <root_user>@localhost <command>. 

For instance, if I wanted to check the version of the Debian operation system on a Raspberry Pi I would run ssh pi@localhost cat /etc/debian_version. These commands can be run in a LabVIEW VI by using the System Exec VI, so now you have a way to execute commands outside of the LV chroot.