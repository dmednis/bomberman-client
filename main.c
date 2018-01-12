#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <ncurses.h>

#include "helpers.h"
#include "constants.h"
#include "drawing.h"

// Functions
void setupServer();
int joinRequest(char[NICKNAME_LENGTH]); // Sends joint request and receives response
void handleInput(int key);
void *serverCallback(void *arg); // Multi-thread callbakc function for handling server responses
void packet_handler(const unsigned char replay[]); // Handles different packets received from server

//Server response handling functions
void lobbyStatus(const unsigned char *replay);

// Global variables
int socket_descriptor;
struct sockaddr_in server;
bool game_started = false;

int player_ID;
char nickname[NICKNAME_LENGTH];


int main(int argc, char *argv[]) {
    char input[USER_INPUT];
    int key;
    pthread_t server_thread, lobby_thread;

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

    puts("Waiting for the game to start \n");

    // Starts a thread for server responses
    pthread_create(&server_thread, NULL, serverCallback, NULL);

    // Checks user input
    // TODO: needs to changed to check user game window input
    while (strcmp(fgets(input, NICKNAME_LENGTH, stdin), "end\n") != 0){

        ///////////////////////// DEBUGING /////////////////////////
        if (send(socket_descriptor, input, strlen(input), 0) < 0) {
            puts("Send failed");
        }
        bzero(input, USER_INPUT);
        ///////////////////////// DEBUGING /////////////////////////
    }

//    while ((key = wgetch(game_window)) != 27) {
//        printf("Pressed %c key, code: %d \n", key, key);
//        ///////////////////////// DEBUGING /////////////////////////
//        if (send(socket_descriptor, input, strlen(input), 0) < 0) {
//            puts("Send failed");
//        }
//        bzero(input, USER_INPUT);
//        ///////////////////////// DEBUGING /////////////////////////
//    }

    return 0;
}


int joinRequest(char nickname[NICKNAME_LENGTH]) {
    unsigned char join_packet[NICKNAME_LENGTH + 1];
    unsigned char response[JOIN_RESPONSE];
    unsigned char response_code = NULL;
    int player_ID = NULL;

    bzero(join_packet, NICKNAME_LENGTH + 1);
    join_packet[0] = JOIN_PACKET_CODE;
    memmove(join_packet + 1, nickname, strlen(nickname));
    puts((const char *) join_packet); //TODO: logging

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
                    puts("Active game on server, please wait!\n");
                    // TODO: start sending keepalive packet in a new thread
                    printf("response code is %d \n", response_code);
                    player_ID = response[2];
                    break;

                case ACTIVE_GAME:
                    puts("Active game on server, please wait!\n");
                    break;

                case FULL_SERVER:
                    puts("Server is full, please wait!\n");
                    break;

                default:break;
            }
        }
    }

    return player_ID;
}


void *serverCallback(void *arg) {
    unsigned char server_replay[RESPONSE_LENGTH];
    ssize_t read_size;

    // Checks whether server hasn't disconnected
    while ((read_size = recv(socket_descriptor, server_replay, RESPONSE_LENGTH, 0)) > 0) {
        ///////////////////////// DEBUGING /////////////////////////
        printf("[1] %s \n", server_replay);
        ///////////////////////// DEBUGING /////////////////////////
        packet_handler(server_replay);
        bzero(server_replay, 2000);
    }

    if (read_size == 0) {
        puts("Server disconnected");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("receiving failed");
    }

    return NULL;
}

void packet_handler(const unsigned char replay[RESPONSE_LENGTH]) {
    unsigned char response_code = replay[0];

    switch (response_code) {
        case LOBBY_RESPONSE_CODE:
            lobbyStatus(replay);
            break;

        case GAME_START_CODE:
            break;

        case MAP_UPDATE_CODE:
            break;

        case OBJECTS_CODE:
            break;

        case GAME_OVER_CODE:
            break;

        default: break;
    }
}

void lobbyStatus(const unsigned char *replay) {
    pthread_t lobby_thread;

    pthread_create(&lobby_thread, NULL, lobbyCallback, NULL);
    draw_lobby_info(replay);
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

void handleInput(int key) {
//    printf("Input: %d \n", getch());

}

