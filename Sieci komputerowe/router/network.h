// Marcin Sarnecki 323034

#pragma once
#include <time.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

class Network {
public:
    uint32_t ip_address;
    uint8_t mask_length;
    uint32_t dist;
    uint32_t via;
    uint32_t broadcast;
    time_t last_update;
    uint32_t old_dist;

    Network(uint32_t ip_addr, uint8_t m_len, uint32_t d, uint32_t v, uint32_t bcast);
};

