#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "helpers.h"

const char *JOIN_PACKET_CODE = "1";

int socket_desc;

void threadFunc() {
    char input[200];

    while (strcmp(gets(input), "exit") != 0) {
        if (send(socket_desc, input, strlen(input), 0) < 0) {
            puts("Send failed");
            exit(1);
        } else {
            printf("[2] %s \n", input);
        }
        bzero(input, 200);
    }
}

int join_request(char nickname[23]) {
    char join_packet[24];
    bzero(join_packet, 24);
    prepend(join_packet, JOIN_PACKET_CODE);
    strcat(join_packet + 1, nickname);
}

int main(int argc, char *argv[]) {
    struct sockaddr_in server;
    char input[200];
    char server_reply[2000];
    int read_size;
    pthread_t rec_thread;

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr("172.20.10.2");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    //Connect to remote server
    if (connect(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
        puts("connect error");
        return 1;
    }

    puts("Connected\n");


    pthread_create(&rec_thread, NULL, threadFunc, NULL);


    //Receive a reply from the server
    //Receive a message from client

    while ((read_size = recv(socket_desc, server_reply, 2000, 0)) > 0) {
        //Send the message back to client
        printf("[1] %s \n", server_reply);
        bzero(server_reply, 2000);
    }

    if (read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("recv failed");
    }

    //Free the socket pointer
    free(socket_desc);

    return 0;
}