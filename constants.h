//
// Created by Austris on 07/01/2018.
//

#ifndef CMAKE_BUILD_DEBUG_CONSTANTS_H
#define CMAKE_BUILD_DEBUG_CONSTANTS_H

// SIZES
const int RESPONSE_LENGTH = 4096;
const int USER_INPUT = 2000;
const int NICKNAME_LENGTH = 23;
const int JOIN_RESPONSE = 3;

// PACKET CODES
unsigned const char JOIN_PACKET_CODE = 1;
unsigned const char JOIN_RESPONSE_CODE = 2;
unsigned const char LOBBY_RESPONSE_CODE = 7;
unsigned const char GAME_START_CODE = 8;
unsigned const char MAP_UPDATE_CODE = 9;
unsigned const char OBJECTS_CODE = 10;
unsigned const char GAME_OVER_CODE = 11;

// JOIN RESPONSE CODES
unsigned const char SUCCESSFUL_CONNECTION = 0;
unsigned const char ACTIVE_GAME =  1;
unsigned const char FULL_SERVER =  2;

// LOBBY STATUSES
unsigned const char LOBBY_NOT_READY = 0;
unsigned const char LOBBY_READY =  1;

//SERVER PARAMETERS
const int PORT = 8888;
const char *INET_ADDRESS = "172.20.10.7";

#endif //CMAKE_BUILD_DEBUG_CONSTANTS_H
