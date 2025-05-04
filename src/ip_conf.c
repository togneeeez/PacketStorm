#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifndef IP_CONF_H
#define IP_CONF_H
    #include "../headers/ip_conf.h"
#endif

/* Example main function.
int main() {
    struct IpAddress* addr = newAddress(192,168,1,1);
    printf("IP Address: %s\n", ipToString(addr));
    free(addr);
    return 0;
}
*/

/* Implementation of the function used to instantiate a new
ip address which can later be assigned to hosts or devices. */
struct IpAddress* newAddress(unsigned char oct1, unsigned char oct2, unsigned char oct3, unsigned char oct4) {
    struct IpAddress* res = malloc(sizeof(struct IpAddress));
    res->octs[0] = oct1;
    res->octs[1] = oct2;
    res->octs[2] = oct3;
    res->octs[3] = oct4;
    return res;
}

/* Implementation of the function used to update an already
instantiated ip address (eg. update a host IP address). */
void updateAddress(struct IpAddress *ip, unsigned char oct1, unsigned char oct2, unsigned char oct3, unsigned char oct4) {
    if ((ip != NULL) && (oct1 >= 0) && (oct2 >= 0) && (oct3 >= 0) && (oct4 >= 0))
        ip->octs[0] = oct1;
        ip->octs[1] = oct2;
        ip->octs[2] = oct3;
        ip->octs[3] = oct4;
}

/* Function used to translate an IP address (in decimal) provided
as an argument to string, used sfor printing the IP addresses: */
char* ipToString(struct IpAddress* ip) {
    char* res = malloc(16);
    if (ip != NULL)
        sprintf(res, "%d.%d.%d.%d", ip->octs[0], ip->octs[1], ip->octs[2], ip->octs[3]);
        return res;
    sprintf(res, "?.?.?.?");
    return res;
}
