
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"

WINDOW *lobby_window, *game_window;

void close_window(WINDOW *window) {
    delwin(window);
    curs_set(1);
    endwin();
}

void *lobbyCallback(void *arg) {
    initscr();
    clear();
    curs_set(0);
    noecho();
    lobby_window = newwin(20, 100, 0, 0);

    keypad(lobby_window, TRUE);
    box(lobby_window,0,0);
    wrefresh(lobby_window);

    return NULL;
}

void draw_lobby_info(const unsigned char *replay) {
    int player_count = replay[1];
    char *lobby_status;
    char *player_id;
    char *player_name = malloc(24);
    int id_position = 2;

    //TODO: update status for each player
    for (int i = 0; i < player_count; i++) {
        player_id = (char *) replay[id_position + (25 * i)];
        lobby_status = player_id + 23;
        memmove(player_name, player_id + 1, 23);

        mvwprintw(lobby_window, i, 0, "Player %s status: %d", player_name, lobby_status);
    }
}
