ip link set enp0s3 name loc0
ip link set up dev loc0
ip addr add 172.16.1.14/16 dev loc0
ip link set enp0s8 name loc1
ip link set up dev loc1
ip addr add 192.168.2.10/24 dev loc1
ip link set enp0s9 name loc2
ip link set up dev loc2
ip addr add 10.0.1.2/8 dev loc2