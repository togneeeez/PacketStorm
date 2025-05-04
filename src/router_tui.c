#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h> // For malloc and free

#ifndef IP_CONF_H
#define IP_CONF_H
    #include "../headers/ip_conf.h"
#endif

#ifndef IP_PACKET_H
#define IP_PACKET_H
    #include "../headers/ip_packet.h"
#endif

#ifndef ROUTER_H
#define ROUTER_H
    #include "../headers/router.h"
#endif

#ifndef HOST_H
#define HOST_H
    #include "../headers/host.h"
#endif

int main() {

    int choice = 1;

    while (choice != 0) {
        printf("Welcome to PacketStorm!\n\n");

        printf("1) Add router\n");
        printf("0) Quit\n\n");

        printf("Choose: ");
        scanf("%d", &choice);

        unsigned char octs[4];
        switch (choice) {
            case 0:
                choice = 0;
                break;
            case 1:
                printf("\nChoose the router's IP address (aaa.bbb.ccc.ddd): ");
                scanf("%hhu.%hhu.%hhu.%hhu", &octs[0], &octs[1], &octs[2], &octs[3]);
            
                struct IpAddress* addr = newAddress(octs[0], octs[1], octs[2], octs[3]);
                struct Router* r = newRouter(addr);

                char file[256]; // Ensure this is large enough
                snprintf(file, sizeof(file), "../pipes/%d_%d_%d_%d", octs[0], octs[1], octs[2], octs[3]);
                
                // Check if mkfifo was successful
                if (mkfifo(file, 0666) == -1) {
                    perror("Failed to create FIFO");
                    break; // Handle error appropriately
                }

                int fd = open(file, O_RDONLY);
                if (fd == -1) {
                    perror("Failed to open FIFO");
                    break; // Handle error appropriately
                }

                struct IpPacket* pkt;
                while (1) {
                    pkt = routerRead(r, fd);
                    if (pkt == NULL) {
                        // Handle the case where no packet is read
                        break; // Exit the loop if needed
                    }
                    printf("Press to continue...");
                    getchar(); // Wait for user input
                }
                printf("New router created.\n\n");
                break;
            default:
                printf("\nError: Choice not available!\n");
        }
    }

    return 0;
}
