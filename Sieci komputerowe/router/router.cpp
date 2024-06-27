// Marcin Sarnecki 323034

#include "router.h"
#include "ip.h"

uint32_t Router::DirectNetworkDist(uint32_t ip_address) {
    for (Network& net : directNetworks) {
        uint32_t ip_network = endian(ip_address);
        uint32_t mask = -(1 << (32 - net.mask_length));
        ip_network = endian(ip_network & mask);
        if (ip_network == net.ip_address)  {
            net.last_update = time(nullptr);
            return net.dist;
        }
    }
    return inf;
}


void Router::Update(uint32_t ip_address, uint8_t mask_length, uint32_t dist, uint32_t sender_ip) {
    if(own_ip.find(sender_ip) != own_ip.end()) //pakiet wyslany przez siebie samego
        return;
    if(dist == inf) //siec z nieskonczona odlegloscia niczego nie wniesie
        return;
    for(Network& network : directNetworks) 
        if (network.ip_address == ip_address && network.mask_length == mask_length) { //pakiet z informacja o bezposredniej sieci
            if (network.old_dist == dist && network.dist == inf) { //przypadek odnowienia polaczenia
                network.dist = network.old_dist;
                network.last_update = time(nullptr);
            }
            if(network.dist == dist) //pakiey wyslany przez bezposredniego sasiada, update czasu
                network.last_update = time(nullptr);
            return;
        }
    for (Network& network : networks) 
        if (network.ip_address == ip_address && network.mask_length == mask_length) { 
            uint32_t d = DirectNetworkDist(sender_ip) + dist;
            if(d >= inf_lim) //przekrocozny limit
                continue;
            if(d <= network.dist) //na pewno udalo sie cos znalezc, update czasu
                network.last_update = time(nullptr);
            if(d < network.dist) { //cos lepszego - update dystansu i pierwszego routera na trasie
                network.dist = d;
                network.via = sender_ip;
            }
            return;
        }
    uint32_t d = dist + DirectNetworkDist(sender_ip); //siec z pakietu nie byla zapisana - dodajemy nowa siec
    if(d >= inf_lim)
        return;
    networks.push_back(Network(ip_address, mask_length, d, sender_ip, 0));
}


void Router::Print() {
    for (Network network : directNetworks) {
        char buf[20];
        inet_ntop(AF_INET, &(network.ip_address), buf, 20);
        std::cout<<buf<<"/"<<(int)network.mask_length<<" ";
        if (network.dist == inf)
            std::cout<<"unreachable ";
        else
            std::cout<<"distance "<<network.dist<<" ";
        std::cout<<"connected directly\n";
    }
    for (Network network : networks) {
        char buf[20];
        inet_ntop(AF_INET, &(network.ip_address), buf, 20);
        std::cout<<buf<<"/"<<(int)network.mask_length<<" ";
        if (network.dist == inf)
            std::cout<<"unreachable ";
        else
            std::cout<<"distance "<<network.dist<<" ";
        inet_ntop(AF_INET, &(network.via), buf, 20);
        std::cout<<"via "<<buf<<"\n";
    }
    std::cout<<"\n\n";
}

void Router::Clear() {
    for (Network &network : directNetworks)
        if (time(nullptr) - network.last_update > time_to_remove) //bezposrednia siec jako unreachable jesli nie dostalismy zadnego pakietu z niej
            network.dist = inf;
    for (auto network = networks.begin(); network != networks.end();)
        if (network->dist == inf && time(nullptr) - network->last_update > time_to_remove) //wywalamy zwykla siec jesli dystans = inf oraz minal czas na update
            network = networks.erase(network);
        else if (time(nullptr) - network->last_update > time_to_remove) {//jesli dystans =/= inf ale za dlugo nie mielismy zadnej informacji o tej sieci to zmieniamy dystans na inf
            network->dist = inf;
            network->last_update = time(nullptr);//update czasu zeby jeszcze przez chwile sie wyswietlalo
        }
        else
            network++;
}

void Router::Create_Socket() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(54321);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    int broadcastEnable=1;
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
    if (sockfd < 0) {
        std::cerr << "socket error: " << std::strerror(errno) << std::endl;
        exit(1);
    }

    bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address));
}

void Router::Receive()
{
    time_t start = time(nullptr);
    while (time(nullptr) - start < round_time) {
        struct sockaddr_in sender;
        socklen_t sender_len = sizeof(sender);
        uint8_t pack[IP_MAXPACKET + 1];
        fd_set descriptors;
        FD_ZERO(&descriptors);
        FD_SET(sockfd, &descriptors);
        struct timeval tv;
        tv.tv_sec = round_time - (time(nullptr) - start);
        tv.tv_usec = 0;
        if (select(sockfd + 1, &descriptors, NULL, NULL, &tv) == 0)
            break;
        ssize_t packet_len = recvfrom(sockfd, pack, IP_MAXPACKET, 0, (struct sockaddr *)&sender, &sender_len);
        if (packet_len < 0) {
            std::cerr << "recvfrom error: " << std::strerror(errno) << std::endl;
            exit(1);
        }
        uint32_t sender_ip = sender.sin_addr.s_addr;
        if (packet_len == 9) {
            uint32_t ip_address = endian(*((uint32_t *)pack));
            uint8_t mask_length = pack[4];
            uint32_t dist = endian(*(uint32_t *)(pack + 5));
            Update(ip_address, mask_length, dist, sender_ip);
        }
    }
}

bool Router::Send_single_packet(uint32_t dest, uint32_t address, uint8_t mask, uint32_t dist) {
    struct sockaddr_in recipient;
    recipient.sin_addr.s_addr = dest;
    recipient.sin_family = AF_INET;
    recipient.sin_port = htons(54321);
    uint8_t pack[9];
    *((uint32_t *)pack) = endian(address);//sieciowa kolejnosc
    pack[4] = mask;
    *((uint32_t *)(pack + 5)) = endian(dist);//sieciowa kolejnosc
    if(sendto(sockfd, pack, 9, 0, (struct sockaddr *)&recipient, sizeof(recipient)) < 0)
        return false;
    return true;
}

void Router::Send() {
    for (Network &dest : directNetworks) //wysylamy bezposrednie w bezposrednie
        for (Network net : directNetworks) 
            if(!Send_single_packet(dest.broadcast, net.ip_address, net.mask_length, dest.ip_address == net.ip_address ? net.old_dist : net.dist)) //zakleszczenie
                dest.dist = inf;
    for (Network &dest : directNetworks) //wysylamy zwykle w bezposrednie
        for (Network net: networks) 
            if(!Send_single_packet(dest.broadcast, net.ip_address, net.mask_length, net.dist)) 
                dest.dist = inf;
}

void Router::Input() {
    int n, distance;
    std::string ip_string, d;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> ip_string >> d >> distance;
        uint32_t broadcast = network_broadcast(ip_string);
        uint32_t net = network_addr(ip_string);
        uint8_t mask_len = mask_length(ip_string);
        uint32_t addr;
        int slash_pos = ip_string.find("/");
        std::string ip_str = ip_string.substr(0, slash_pos);
        inet_pton(AF_INET, ip_str.c_str(), &addr);
        own_ip.insert(addr);
        directNetworks.push_back(Network(net, mask_len, distance, 0, broadcast));
    }
}

void Router::Main_Loop() {
    while(true) {
        Receive();
        Send();
        Print();
        Clear();
    }
}