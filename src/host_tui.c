#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

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
    
    int choice = 3;

    while (choice != 0) {
        printf("Welcome to PacketStorm!\n\n");

        printf("1) Add host\n");
        printf("2) Go back\n\n");

        printf("Choose: ");
        scanf("%d", &choice); // Legge il valore di choice dall'utente

        switch(choice) {
            case 1:
                char octs[4];
                printf("\nChoose the host's IP address:\n");
                printf("Octet 1: ");
                scanf("%d", &octs[0]);
                printf("Octet 2: ");
                scanf("%d", &octs[1]);
                printf("Octet 3: ");
                scanf("%d", &octs[2]);
                printf("Octet 4: ");
                scanf("%d", &octs[3]);
                struct IpAddress* addr = newAddress(octs[0],octs[1],octs[2],octs[3]);

                printf("\nChoose the host's subnet mask:\n");
                printf("Octet 1: ");
                scanf("%d", &octs[0]);
                printf("Octet 2: ");
                scanf("%d", &octs[1]);
                printf("Octet 3: ");
                scanf("%d", &octs[2]);
                printf("Octet 4: ");
                scanf("%d", &octs[3]);
                struct IpAddress* smask = newAddress(octs[0],octs[1],octs[2],octs[3]);
                printf("\nChoose the host's default gateway:\n");
                printf("Octet 1: ");
                scanf("%d", &octs[0]);
                printf("Octet 2: ");
                scanf("%d", &octs[1]);
                printf("Octet 3: ");
                scanf("%d", &octs[2]);
                printf("Octet 4: ");
                scanf("%d", &octs[3]);
                struct IpAddress* dgat = newAddress(octs[0],octs[1],octs[2],octs[3]);
                struct Host* h = newHost(addr, smask, dgat);

                // Create the FIFO file name
                char file[20];
                sprintf(file, "../pipes/%d_%d_%d_%d", octs[0], octs[1], octs[2], octs[3]);

                // Open the FIFO for writing
                int fd = open(file, O_WRONLY | O_NONBLOCK);

                if (fd < 0) {
                    printf("Error opening FIFO file\n");
                    break;
                }

                while (1) {
                    printf("Enter the destination IP address: ");
                    printf("Octet 1: ");
                    scanf("%d", &octs[0]);
                    printf("Octet 2: ");
                    scanf("%d", &octs[1]);
                    printf("Octet 3: ");
                    scanf("%d", &octs[2]);
                    printf("Octet 4: ");
                    scanf("%d", &octs[3]);
                    struct IpAddress* destAddr = newAddress(octs[0], octs[1], octs[2], octs[3]);

                    // Assuming the source IP address is the same as the router's IP address
                    struct IpAddress* srcAddr = newAddress(octs[0], octs[1], octs[2], octs[3]);

                    printf("Enter the packet's data: ");
                    char data[65515];
                    scanf("%s", &data);
            
                    struct IpPacket* pkt = newPacket(srcAddr, destAddr, data);
                    // Assuming hostWrite function is defined elsewhere
                    // hostWrite(h, fd, pkt);
                    // For demonstration purposes, we'll use write function
                    write(fd, pkt, sizeof(struct IpPacket));

                    // Wait for user input before sending the next packet
                    printf("Press enter to send the next packet...\n");
                    getchar();
                }
                break;
            default:
                break;
        }
    }
}
