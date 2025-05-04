#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef HOST_H
#define HOST_H
    #include "../headers/host.h"
#endif

#ifndef IP_CONF_H
#define IP_CONF_H
    #include "../headers/ip_conf.h"
#endif

#ifndef IP_PACKET_H
#define IP_PACKET_H
    #include "../headers/ip_packet.h"
#endif


/* Implementation of the function used to change the power
state of the virtual host provided as an argument from on to off and viceversa. */
void powerBtn(struct Host *host) {
    if (host != NULL)
        if (host->isSwitchedOn) 
            host->isSwitchedOn = false;
        else
            host->isSwitchedOn = true;
}

/* Implementation of the function used to change the
IP address, provided as an argument, of the virtual host 
provided as an argument. */
void setIpAddr(struct Host* host, struct IpAddress* ip) {
    if ((host != NULL) && (ip != NULL))
        host->localIpAddr = ip;
}

/* Implementation of the function used to get the IP
address of a given virtual host. */
struct IpAddress* getIpAddr(struct Host* host) {
    if (host != NULL)
        return host->localIpAddr;
}

/* Implementation of the function used to change the
subnet mask, provided as an argument, of the virtual host 
provided as an argument. */
void setSubMask(struct Host* host, struct IpAddress* submask) {
    if ((host != NULL) && (submask != NULL))
        host->localSubMask = submask;
}

/* Implementation of the function used to get the
subnet mask of a given virtual host. */
struct IpAddress* getSubMask(struct Host *host) {
    if (host != NULL)
        return host->localSubMask;
}

/* Implementation of the function used to change the
default gateway, provided as an argument, of the virtual host 
provided as an argument. */
void setDefGateway(struct Host* host, struct IpAddress* defGateway) {
    if (host != NULL && defGateway != NULL)
        host->localDefGateway = defGateway;
}

/* Implementation of the function used to get the
default gateway of a given virtual host. */
struct IpAddress* getDefGateway(struct Host* host) {
    if (host != NULL)
        return host->localDefGateway;
}

/* Implementation of the newHost(struct IpAddress*, struct IpAddress*, struct IpAddress*)
function, used to instantiate a new virtual host inside a network. */
struct Host* newHost(struct IpAddress* ip, struct IpAddress* smask, struct IpAddress* gateway) {
    struct Host* res = malloc(sizeof(struct Host));
    setIpAddr(res, ip);
    setSubMask(res, smask);
    setDefGateway(res, gateway);
    res->isSwitchedOn = false;
    return res;
}

/* Implementation of the deleteHost(struct Host*) function, used to delete an
existing virtual host inside a network, provided as an argument. */
void deleteHost(struct Host* device) {
    if ((device != NULL) && (device->localIpAddr != NULL) && (device->localSubMask != NULL) && (device->localDefGateway != NULL))
        free(device->localIpAddr);
        free(device->localSubMask);
        free(device->localDefGateway);
        device->isSwitchedOn = false;
        free(device);
}

void hostWrite(struct Host* device, int fd, struct IpPacket* pkt) {
    if (fd) {
        long int li_buff;
        short int si_buff;
        int i_buff;
        char c_buff;
        bool b_buff;

        c_buff = pkt->header.vers_headerLength;
        write(fd, &c_buff, sizeof(pkt->header.vers_headerLength));
        c_buff = pkt->header.serviceType;
        write(fd, &c_buff, sizeof(pkt->header.serviceType));
        si_buff = pkt->header.totalLength;
        write(fd, &si_buff, sizeof(pkt->header.totalLength));
        si_buff = pkt->header.identification;
        write(fd, &si_buff, sizeof(pkt->header.identification));
        b_buff = pkt->header.f_reserved;
        write(fd, &b_buff, sizeof(pkt->header.f_reserved));
        b_buff = pkt->header.f_dontFragment;
        write(fd, &b_buff, sizeof(pkt->header.f_dontFragment));
        b_buff = pkt->header.f_moreFragments;
        write(fd, &b_buff, sizeof(pkt->header.f_moreFragments));
        si_buff = pkt->header.fragmentOffset;
        write(fd, &si_buff, sizeof(pkt->header.fragmentOffset));
        c_buff = pkt->header.timeToLive;
        write(fd, &c_buff, sizeof(pkt->header.timeToLive));
        c_buff = pkt->header.protocol;
        write(fd, &c_buff, sizeof(pkt->header.protocol));
        si_buff = pkt->header.headerChecksum;
        write(fd, &si_buff, sizeof(pkt->header.headerChecksum));

        c_buff = pkt->header.srcIpAddr->octs[0];
        write(fd, &c_buff, sizeof(char));
        c_buff = pkt->header.srcIpAddr->octs[1];
        write(fd, &c_buff, sizeof(char));
        c_buff = pkt->header.srcIpAddr->octs[2];
        write(fd, &c_buff, sizeof(char));
        c_buff = pkt->header.srcIpAddr->octs[3];
        write(fd, &c_buff, sizeof(char));

        c_buff = pkt->header.destIpAddr->octs[0];
        write(fd, &c_buff, sizeof(char));
        c_buff = pkt->header.destIpAddr->octs[1];
        write(fd, &c_buff, sizeof(char));
        c_buff = pkt->header.destIpAddr->octs[2];
        write(fd, &c_buff, sizeof(char));
        c_buff = pkt->header.destIpAddr->octs[3];
        write(fd, &c_buff, sizeof(char));

        // Let's write the IP payload
        char* data = pkt->data;
        write(fd, data, sizeof(pkt->data));

    }
}