#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef IP_CONF_H
#define IP_CONF_H
    #include "../headers/ip_conf.h"
#endif


struct IpPacket {
    /* Structure to describe the IP packet header structure. */
    struct IpHeader {
        /* Mind that: 
            - char is 8 bit;
            - short int is 16 bit;
            - bool is 1 bit;
            - long int is 32 bit;
            - int is 16 bit;
        */

        /* This char variable is used to represent each of the
        first 4-bit fields of the IP header, containing the version
        of the IP protocol used and the length of the header part of
        the packet:
        - H: contains the version of the IPv4 packet, which 
        is a constant of  */
        char vers_headerLength;


        char serviceType;
        short int  totalLength;
        short int identification;

        /* These are part of the 3-bit header field of the IP header,
        containing the packet's flags (RES, DF, MF). */
        bool f_reserved;
        bool f_dontFragment;
        bool f_moreFragments;


        short fragmentOffset; 
        char timeToLive;
        char protocol;
        short int headerChecksum;
        struct IpAddress* srcIpAddr;
        struct IpAddress* destIpAddr;
        int options;
        int padding;
    } header;

    /* Buffer used to store the packet payload. */
    char* data;
};

void read_data();
struct IpPacket* newPacket(struct IpAddress*, struct IpAddress*, char*);

/* IpPacket utilities */
void printHostInfo(struct IpPacket*);



