//
// Created by Austris on 07/01/2018.
//

#ifndef CMAKE_BUILD_DEBUG_CONSTANTS_H
#define CMAKE_BUILD_DEBUG_CONSTANTS_H

// SIZES
const int RESPONSE_LENGTH = 2000;
const int USER_INPUT = 2000;
const int NICKNAME_LENGTH = 23;
const int JOIN_RESPONSE = 3;

// PACKET CODES
const char JOIN_PACKET_CODE = '1';
const char JOIN_RESPONSE_CODE = '2';

// RESPONSE CODES
const int SUCCESSFUL_CONNECTION = '0';
const int ACTIVE_GAME =  '1';
const int FULL_SERVER =  '2';

//SERVER PARAMETERS
const int PORT = 8888;
const char *INET_ADDRESS = "172.20.10.2";

#endif //CMAKE_BUILD_DEBUG_CONSTANTS_H
