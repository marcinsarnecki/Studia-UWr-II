// Marcin Sarnecki 323034

#include "network.h"

Network::Network(uint32_t ip_addr, uint8_t m_len, uint32_t d, uint32_t v, uint32_t bcast) {
    ip_address = ip_addr;
    mask_length = m_len;
    dist = d;
    via = v;
    broadcast = bcast;
    last_update = time(nullptr);
    old_dist = dist;
}