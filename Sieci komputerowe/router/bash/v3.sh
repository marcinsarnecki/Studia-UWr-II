ip link set enp0s3 name loc2
ip link set up dev loc2
ip addr add 10.0.1.1/8 dev loc2
ip link set enp0s8 name loc3
ip link set up dev loc3
ip addr add 192.168.5.43/24 dev loc3
