#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

struct IpAddress {
    unsigned char octs[4];
};

struct IpAddress* newAddress(unsigned char, unsigned char, unsigned char, unsigned char);
void updateAddress(struct IpAddress*,unsigned char, unsigned char, unsigned char, unsigned char);

char* ipToString(struct IpAddress*);