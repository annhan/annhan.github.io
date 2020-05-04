# Update firmware dependencies and install rpi-eeprom
```
sudo apt update
sudo apt dist-upgrade
sudo reboot
sudo apt install rpi-eeprom
rpi-eeprom-update -h
```


# Check if the bootloader is up to date
```
rpi-eeprom-update
```

# Install a specific image
```
sudo rpi-eeprom-update -f /lib/firmware/raspberrypi/bootloader/critical/pieeprom-2020-04-16.bin
sudo reboot
```

# Syslog messages
```
sudo grep rpi-eeprom-update /var/log/syslog
```