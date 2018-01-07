#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

#include "helpers.h"
#include "constants.h"

// Functions
void setupServer();
int joinRequest(char[NICKNAME_LENGTH]);
void *serverCallback(void *arg);

// Global variables
int socket_descriptor;
struct sockaddr_in server;

int player_ID;
char nickname[NICKNAME_LENGTH];


int main(int argc, char *argv[]) {
    char input[USER_INPUT];
    pthread_t server_thread;

    //Creates socket
    setupServer();

    //Connects to the server
    if (connect(socket_descriptor, (struct sockaddr *) &server, sizeof(server)) < 0) {
        puts("connect error");
        return 1;
    } else {
        puts("Connected");
    }


    // Gets user name from input
    puts("Enter your user name\n");
    bzero(nickname, NICKNAME_LENGTH);
    fgets(nickname, NICKNAME_LENGTH, stdin);
    player_ID = joinRequest(nickname);

    // Starts a thread for server responses
    pthread_create(&server_thread, NULL, serverCallback, NULL);

    // Checks user input
    while (strcmp(fgets(input, NICKNAME_LENGTH, stdin), "end\n") != 0){
        ///////////////////////// DEBUGING /////////////////////////
        if (send(socket_descriptor, input, strlen(input), 0) < 0) {
            puts("Send failed");
        }
        bzero(input, USER_INPUT);
        ///////////////////////// DEBUGING /////////////////////////
    }

    return 0;
}


int joinRequest(char nickname[NICKNAME_LENGTH]) {
    char join_packet[NICKNAME_LENGTH + 1];
    char response[JOIN_RESPONSE];
    char response_code = NULL;
    int player_ID = NULL;

    bzero(join_packet, NICKNAME_LENGTH + 1);
    prepend_char(join_packet, JOIN_PACKET_CODE);
    join_packet[0] = JOIN_PACKET_CODE;
    memmove(join_packet + 1, nickname, strlen(nickname));
    puts(join_packet); //TODO: logging

    if (send(socket_descriptor, join_packet, NICKNAME_LENGTH + 1, 0) < 0) {
        puts("Send failed");
    }

    if (read(socket_descriptor, response, 3) < 0) {
        puts("Read failed");
    } else {
        if (response[0] == JOIN_RESPONSE_CODE) {
            response_code = response[1];

            switch (response_code) {
                case SUCCESSFUL_CONNECTION:
                    // Converts char to integer
                    player_ID = response[2] - '0';
                    break;

                case ACTIVE_GAME:
                    puts("Active game on server, please wait!\n");

                case FULL_SERVER:
                    puts("Server is full, please wait!\n");

                default:break;
            }
        }
    }

    return player_ID;
}


void *serverCallback(void *arg) {
    char server_reply[RESPONSE_LENGTH];
    ssize_t read_size;

    // Checks whether server hasn't disconnected
    while ((read_size = recv(socket_descriptor, server_reply, RESPONSE_LENGTH, 0)) > 0) {
        ///////////////////////// DEBUGING /////////////////////////
        printf("[1] %s \n", server_reply);
        ///////////////////////// DEBUGING /////////////////////////
        bzero(server_reply, 2000);
    }

    if (read_size == 0) {
        puts("Server disconnected");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("receiving failed");
    } else {

    }

    return NULL;
}

void setupServer() {
    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_descriptor == -1) {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = inet_addr(INET_ADDRESS);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
}

