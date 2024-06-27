ip link set enp0s3 name loc1
ip link set up dev loc1
ip addr add 192.168.2.5/24 dev loc1
ip link set enp0s8 name loc3
ip link set up dev loc3
ip addr add 192.168.5.5/24 dev loc3
