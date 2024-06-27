// Marcin Sarnecki 323034

#include <netinet/ip_icmp.h>
#include <assert.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/select.h>

#include "functions.c"

#ifndef TRACEROUTE
#define TRACEROUTE

uint16_t checksum(void* buff, int len) {
    int sum = 0;
    uint16_t *ptr = buff;
    while(len > 0) {
        sum += *ptr++;
        len -= 2;
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    return (uint16_t)~((sum >> 16) + sum);
}


int icmp_send(int ttl, int sockfd, char *ip) {
    struct icmp header;
    header.icmp_type = ICMP_ECHO;
    header.icmp_code = 0;
    header.icmp_id = (uint16_t)getpid();//w pakiecie wysylamy id procesu zeby rozroznic jednoczesnie dzialajace procesy
    header.icmp_seq = ttl;
    header.icmp_cksum = 0;
    header.icmp_cksum = checksum((uint16_t*)&header, sizeof(header));

    struct sockaddr_in dest_addr;
    bzero(&dest_addr, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &dest_addr.sin_addr);

    Setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));
    return Sendto(sockfd, &header, sizeof(header), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));
}

uint8_t icmp_receive(int sockfd, struct icmp* header, char* ip_in_string) {
    struct sockaddr_in sender;
    socklen_t sender_len = sizeof(sender);
    u_int8_t buffer[IP_MAXPACKET];

    Recvfrom(sockfd, buffer, IP_MAXPACKET, MSG_DONTWAIT, (struct sockaddr*)&sender, &sender_len);

    struct ip* ip_header = (struct ip*)buffer;
    strcpy(ip_in_string, inet_ntoa(ip_header->ip_src));

    ssize_t ip_header_len = 4 * ip_header->ip_hl;// 32bit word -> byte, wiec *4
    struct icmp* icmp_header = (struct icmp*)(buffer + ip_header_len);// fragment icmp

    if (icmp_header->icmp_type == ICMP_TIME_EXCEEDED) {// szczegolny przypadek, pakiet nie dotarl bo skonczyl sie time to live
        struct ip* inner_ip_header = (struct ip*)(buffer + ip_header_len + 8);// przesuwamy do oryginalnego pakietu ip
        ip_header_len = 4 * inner_ip_header->ip_hl;
        icmp_header = (struct icmp*)((uint8_t*)inner_ip_header + ip_header_len);//w oryginalnym pakiecie przesuwamy sie o header
    }

    memcpy(header, icmp_header, sizeof(struct icmp));//kopiujemy znaleziony fragment icmp do headera przekazanego do funkcji

    return header->icmp_type;
}

void check_input(int argc, char **argv) {
    if(argc != 2) {
        printf("Traceroute takes exactly 1 argument\nUsage: ./traceroute ip_address\n");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in sa;
    int res = inet_pton(AF_INET, argv[1], &(sa.sin_addr));
    if(res <= 0) {
        printf("Wrong ip address passed!\n");
        exit(EXIT_FAILURE);
    }
}

void update_time(struct timeval *sum, struct timeval *start) {
    struct timeval current, interval;
    gettimeofday(&current, NULL);
    timersub(&current, start, &interval);
    timeradd(sum, &interval, sum);
}

void print(char ip_addresses[][20], int packets, int ttl, struct timeval sum) {
    int all_same = 1;
    long long ms = sum.tv_usec / 3000;
    if (strcmp(ip_addresses[0], ip_addresses[1]) != 0 || strcmp(ip_addresses[1], ip_addresses[2]) != 0) 
        all_same = 0;
    if (packets == 3 && all_same == 1) {
        printf("%d. %s %lldms\n", ttl, ip_addresses[0], ms);
    } else if (packets == 3 && all_same == 0) {
        printf("%d %s %s %s %lldms\n", ttl, ip_addresses[0], ip_addresses[1], ip_addresses[2], ms);
    } else if (packets == 0) {
        printf("%d. *\n", ttl);
    } else {
        printf("%d. ", ttl);
        for(int i = 0; i < packets; i++)
            printf("%s ", ip_addresses[i]);
        printf(" ???\n");
    }
}

int main(int argc, char **argv) {
    check_input(argc, argv);
    char ip[INET_ADDRSTRLEN];
    strcpy(ip, argv[1]);

    int sockfd = Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    for(int ttl = 1; ttl <= 30; ttl++) {
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(sockfd, &rfds);

        int packets = 0;
        for(int i = 1; i <= 3; i++) 
            icmp_send(ttl, sockfd, ip);

        struct timeval sending_start;
        struct timeval sum = {0,0};
        struct timeval time_limit = {1, 0};

        gettimeofday(&sending_start, NULL);
        char ip_addresses[3][20];
        int end = 0;
        while(packets < 3) {
            if(Select(sockfd + 1, &rfds, NULL, NULL, &time_limit) == 0) 
                break;
            struct icmp header = {0};
            uint8_t type = icmp_receive(sockfd, &header, ip_addresses[packets]);
            if(header.icmp_id == getpid() && header.icmp_seq == ttl) {
                packets++;
                update_time(&sum, &sending_start);
                if(type == ICMP_ECHOREPLY) 
                    end = 1;
            }
        }
        print(ip_addresses, packets, ttl, sum);
        if(end == 1)
            exit(EXIT_SUCCESS);
    }
    return EXIT_SUCCESS;
}

#endif