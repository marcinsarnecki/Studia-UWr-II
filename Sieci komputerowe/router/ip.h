// Marcin Sarnecki 323034

#include <string>
#include <netinet/ip.h>
#include <arpa/inet.h>

uint32_t endian(uint32_t x);

uint32_t network_broadcast(std::string network_str);

uint32_t network_addr(std::string network_str);

uint8_t mask_length(std::string network_str);