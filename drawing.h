#include <ncurses.h>


#ifndef BOMBERMAN_CLIENT_DRAWING_H
#define BOMBERMAN_CLIENT_DRAWING_H

void close_window(WINDOW *window);
void *lobbyCallback(void *arg);
void draw_lobby_info(const unsigned char *replay);

#endif //BOMBERMAN_CLIENT_DRAWING_H
