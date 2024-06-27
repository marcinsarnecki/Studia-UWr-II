// Marcin Sarnecki 323034

#pragma once

#include <list>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <string>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <set>
#include "network.h"

const uint32_t inf = 1000000;
// const uint32_t inf = UINT32_MAX;
const int round_time = 1;
const int time_to_remove = 3 * round_time;
const uint32_t inf_lim = 30;

class Router {
public:
    int sockfd;
    std::list<Network> networks, directNetworks;
    std::set<int> own_ip;
    
    uint32_t DirectNetworkDist(uint32_t);

    void Create_Socket();
    void Clear();
    void Print();
    void Receive();
    void Send();
    bool Send_single_packet(uint32_t, uint32_t, uint8_t, uint32_t);
    void Update(uint32_t, uint8_t, uint32_t, uint32_t);
    void Input();
    void Main_Loop();
};