// Marcin Sarnecki 323034

#include "ip.h"

uint32_t endian(uint32_t value) {
    return ((value & 0x000000FF) << 24) |
           ((value & 0x0000FF00) << 8)  |
           ((value & 0x00FF0000) >> 8)  |
           ((value & 0xFF000000) >> 24);
}

uint32_t network_broadcast(std::string network_str) {
    uint32_t addr = network_addr(network_str);
    uint8_t mask_len = mask_length(network_str);
    uint32_t mask = -(1 << (32 - mask_len));
    addr = endian(addr);
    uint32_t broadcast = addr | (~mask);
    broadcast = endian(broadcast);
    return broadcast;
}

uint32_t network_addr(std::string network_str) {
    int slash_pos = network_str.find("/");
    std::string ip_str = network_str.substr(0, slash_pos);
    uint8_t mask_len = stoi(network_str.substr(slash_pos + 1, 2));
    uint32_t mask = -(1 << (32 - mask_len));
    uint32_t addr;
    inet_pton(AF_INET, ip_str.c_str(), &addr);
    addr = endian(addr);
    uint32_t network = addr & mask;
    network = endian(network);
    return network;
}

uint8_t mask_length(std::string network_str) {
    int slash_pos = network_str.find("/");
    uint8_t mask_len = stoi(network_str.substr(slash_pos + 1, 2));
    return mask_len;
}