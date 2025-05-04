#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef ROUTER_H
#define ROUTER_H
    #include "../headers/router.h"
#endif

#ifndef IP_PACKET_H
#define IP_PACKET_H
    #include "../headers/ip_packet.h"
#endif

#ifndef HOST_H
#define HOST_H
    #include "../headers/host.h"
#endif

/* Implementation of newRouter(struct IpAddress*) function, used to
instantiate a new router with the given IpAddress*) */
struct Router* newRouter(struct IpAddress* ip) {
    struct Router* res = malloc(sizeof(struct Router*));
    return res;
}

/* Implementation of setMTU(struct Router*, short int) function, used to
set the MTU paramter, given as a paramter, of a newly created router, given
as a parameter. */
void setMTU(struct Router* device, short int value) {
    if ((device != NULL) && (value > 0) && (value <= 65536))
        device->mtu = value;
}

/* Implementation of getMTU(struct Router*) function, used to get the MTU
parameter of an already existing router, given as a parameter, in an integer format. */
short int getMTU(struct Router* device) {
    if (device != NULL)
        return device->mtu;
}

/* Implementation of printMTU(struct Router*) function, used to get the MTU
parameter of an already existing router, given as a parameter, in a string format. */
char* printMTU(struct Router* device) {
    if (device != NULL)
        printf("MTU: %d\n", getMTU(device));
}

/* Implementation of routerRead(struct Router*, int fd) function, used to
read from an already open pipe, given as an argument, an IP packet. */
struct IpPacket* routerRead(struct Router* device, int fd) {
    struct IpPacket* pkt = malloc(sizeof(struct IpPacket));
    int i_buff;
    short int si_buff;
    long int li_buff;
    char c_buff;
    bool b_buff;
    if (fd)       
        // Reading from unnamed pipe provided as an argument
        read(fd, &c_buff, sizeof(pkt->header.vers_headerLength));
        printf("Vers: %d\n", (c_buff >> 4));
        printf("Header length: %d\n", (c_buff & 0b00001111));
        pkt->header.vers_headerLength = c_buff;

        read(fd, &c_buff, sizeof(pkt->header.serviceType));
        printf("Service Type: %d\n", c_buff);
        pkt->header.serviceType = c_buff;

        read(fd, &si_buff, sizeof(pkt->header.totalLength));
        printf("Total Length: %d\n", si_buff);
        pkt->header.totalLength = si_buff;

        read(fd, &si_buff, sizeof(pkt->header.identification));
        printf("Identification: %d\n",si_buff);
        pkt->header.identification = si_buff;

        read(fd, &b_buff, sizeof(pkt->header.f_reserved));
        printf("Flags (Reserved): ");
        if (b_buff)
            printf("True\n");
        else
            printf("False\n");
        pkt->header.f_reserved = b_buff;

        read(fd, &b_buff, sizeof(pkt->header.f_dontFragment));
        printf("Flags (Don't Fragment): ");
        if (b_buff)
            printf("True\n");
        else
            printf("False\n");
        pkt->header.f_dontFragment = b_buff;

        read(fd, &b_buff, sizeof(pkt->header.f_moreFragments));
        printf("Flags (More Fragments): ");
        if (b_buff)
            printf("True\n");
        else
            printf("False\n");
        pkt->header.f_moreFragments = b_buff;

        read(fd, &si_buff, sizeof(pkt->header.fragmentOffset));
        printf("Fragment Offset: %d\n", si_buff);
        pkt->header.fragmentOffset = si_buff;

        read(fd, &c_buff, sizeof(pkt->header.timeToLive));
        printf("TTL: %d\n", c_buff);
        pkt->header.timeToLive = c_buff;

        read(fd, &c_buff, sizeof(pkt->header.protocol));
        printf("Protocol: %d\n", c_buff);
        pkt->header.protocol = c_buff;

        read(fd, &si_buff, sizeof(pkt->header.headerChecksum));
        printf("Header Checksum: %d\n", si_buff);
        pkt->header.headerChecksum = si_buff;

        char octs[4];
        read(fd, &octs[0], sizeof(unsigned char));
        read(fd, &octs[1], sizeof(unsigned char));
        read(fd, &octs[2], sizeof(unsigned char));
        read(fd, &octs[3], sizeof(unsigned char));
        pkt->header.srcIpAddr = newAddress(octs[0], octs[1], octs[2], octs[3]);
        printf("Source IP Address: %s\n", ipToString(pkt->header.srcIpAddr));

        read(fd, &octs[0], sizeof(unsigned char));
        read(fd, &octs[1], sizeof(unsigned char));
        read(fd, &octs[2], sizeof(unsigned char));
        read(fd, &octs[3], sizeof(unsigned char));
        pkt->header.destIpAddr = newAddress(octs[0], octs[1], octs[2], octs[3]);
        printf("Destination IP Address: %s\n", ipToString(pkt->header.destIpAddr));

        // Let's read the IP payload
        char data[65515];
        read(fd, data, 65515);
        printf("Data: %s\n", data);
        pkt->data = data;

    return pkt;
}