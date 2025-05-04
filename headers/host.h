#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef IP_CONF_H
#define IP_CONF_H
    #include "ip_conf.h"
#endif

#ifndef IP_PACKET_H
#define IP_PACKET_H
    #include "ip_packet.h"
#endif

struct Host {
    struct IpAddress* localIpAddr;
    struct IpAddress* localSubMask;
    struct IpAddress* localDefGateway;
    bool isSwitchedOn;
};

/* Functions' prototypes.*/
void powerBtn(struct Host*);
void setIpAddr(struct Host*,  struct IpAddress*);
struct IpAddress* getIpAddr(struct Host*);
void setSubMask(struct Host*, struct IpAddress*);
struct IpAddress* getSubMask(struct Host*);
void setDefGateway(struct Host*, struct IpAddress*);
struct IpAddress* getDefGateway(struct Host*);
struct Host* newHost(struct IpAddress*, struct IpAddress*, struct IpAddress*);
void deleteHost(struct Host*);
void hostWrite(struct Host*, int, struct IpPacket*);


