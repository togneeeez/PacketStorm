#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef IP_CONF_H
#define IP_CONF_H
    #include "ip_conf.h"
#endif


struct Router {
    short int mtu;
    struct IpAddress netIpAddress;
    struct RoutingTable {
        struct IpAddress destinationNet;
        struct IpAddress subMask;
        struct IpAddress nextHop;
    } rtable;
};

/* Functions' prototypes. */
struct Router* newRouter(struct IpAddress*);
void setMTU(struct Router*, short int);
short int getMTU(struct Router*);
char* printMTU(struct Router*);
struct IpPacket* routerRead(struct Router*, int);


