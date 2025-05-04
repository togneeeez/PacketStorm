#ifndef IP_CONF_H
#define IP_CONF_H
    #include "../headers/ip_conf.h"
#endif

#ifndef IP_PACKET_H
#define IP_PACKET_H
    #include "../headers/ip_packet.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/* Example main function.
int main() {
    struct IpAddress* source = newAddress(192, 168, 1, 10);
    struct IpAddress* destination = newAddress(192, 168, 1, 20);
    struct IpPacket* pkt = newPacket(source, destination);
    printHostInfo(pkt);

    return 0;
}
*/

/* Implementation of the newPacket(struct IpAddress*, struct IpAddress*) function,
used to instantiate a new packet with the given source and 
destination's IP addresses.*/
struct IpPacket* newPacket(struct IpAddress* src, struct IpAddress* dest, char* buffer) {
    struct IpPacket* res = malloc(sizeof(struct IpPacket));
    res->header.vers_headerLength = 0b01000000;
    res->header.serviceType = 0;
    res->header.totalLength = 0;
    res->header.identification = 0;
    res->header.f_reserved = false;
    res->header.f_dontFragment = true;
    res->header.f_moreFragments = false;
    res->header.fragmentOffset = 0;
    res->header.timeToLive = 0;
    res->header.protocol = 0;
    res->header.headerChecksum = 0;
    res->header.srcIpAddr = src;
    res->header.destIpAddr = dest;
    res->header.options = 0;
    res->header.padding = 0;

    res->data = buffer;

    return res;
}

void printHostInfo(struct IpPacket* incoming) {
    char* src_ip = ipToString(incoming->header.srcIpAddr);
    char* dest_ip = ipToString(incoming->header.destIpAddr);
    printf("Source IP Address: %s\n", src_ip);
    printf("Destination IP Address: %s\n", dest_ip);
    free(src_ip);
    free(dest_ip);
}

/* TODO: Implement a function to decipher all the data from an
incoming packet and print out its contents in a human-friendly
format. */
void read_data() {
    
}
