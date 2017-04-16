sudo stty -F /dev/ttyACM0 115200
sleep 5
sudo dd if=./Ambi_Happy.bin of=/dev/ttyACM0
