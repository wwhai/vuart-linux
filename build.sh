sudo rm /dev/vuart
sudo rmmod vuart
make
sudo insmod vuart.ko
lsmod
sudo mknod /dev/vuart c 257 0
sudo chmod 777 /dev/vuart