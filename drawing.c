
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "drawing.h"

// DRAWING TYPES
const int DRAW_LOBBY = 1;
const int DRAW_GAME = 2;

WINDOW *lobby_window, *game_window;
DrawQueue *drawqueue;

DrawQueue *create_draw_queue() {
    DrawQueue *queue = malloc(sizeof(DrawQueue));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return queue;
}

DrawNode *create_draw_node(int draw_node_type, void *draw_node_data) {
    DrawNode *node = malloc(sizeof(DrawNode));
    node->type = draw_node_type;
    node->data = draw_node_data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

DrawNode *push_drawable_node(DrawNode *drawNode) {
    DrawQueue *list = drawqueue;

    if (list->tail != NULL) {
        list->tail->next = drawNode;
        drawNode->prev = list->tail;
        list->tail = drawNode;
    } else {
        list->head = drawNode;
        list->tail = drawNode;
    }

    list->size++;

    return drawNode;
}

DrawNode *pop_node() {
    DrawQueue *list = drawqueue;
    DrawNode *toPop;

    if (list->head != NULL) {
        toPop = list->head;
        if (list->head->next != NULL) {
            list->head->next->prev = NULL;
        }
        list->head = list->head->next;
    } else {
        return NULL;
    }

    if (list->head == NULL) {
        list->tail = NULL;
    }

    return toPop;
};

LobbyDrawable *create_lobby_drawable() {
    LobbyDrawable *queue = malloc(sizeof(LobbyDrawable));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return queue;
}

LobbyItem *create_lobby_item(int id, int status, char *name) {
    LobbyItem *node = malloc(sizeof(LobbyItem));
    node->player_id = id;
    node->status = status;
    node->name = name;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

LobbyItem *push_lobby_item(LobbyDrawable *list, LobbyItem *lobby_item) {

    if (list->tail != NULL) {
        list->tail->next = lobby_item;
        lobby_item->prev = list->tail;
        list->tail = lobby_item;
    } else {
        list->head = lobby_item;
        list->tail = lobby_item;
    }

    list->size++;

    return lobby_item;
}

void dispose_lobby_drawable(LobbyDrawable *list) {
    LobbyItem *cursor, *tmp;

    if (list->head != NULL) {
        cursor = list->head->next;
        list->head->next = NULL;
        while (cursor != NULL) {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
}

void close_window(WINDOW *window) {
    delwin(window);
    curs_set(1);
    endwin();
}

void *draw_callback(void *arg) {
    drawqueue = create_draw_queue();

    initscr();
    clear();
    curs_set(0);
    noecho();
    lobby_window = newwin(20, 100, 0, 0);

    keypad(lobby_window, TRUE);
    box(lobby_window, 0, 0);
    wrefresh(lobby_window);

    while (drawqueue != NULL) {
        if (drawqueue->size > 0) {
            DrawNode *drawable = pop_node();
            draw(drawable);
        }
    }
    return NULL;
}

void draw(DrawNode *drawable) {
    switch (drawable->type) {
        case DRAW_LOBBY: {
            draw_lobby((LobbyDrawable *) drawable->data);
            break;
        }

        case DRAW_GAME: {
            break;
        }

        default: {
            break;
        }
    }
}


void queue_lobby_info(unsigned char *reply) {
    LobbyDrawable *lobbydrawable = create_lobby_drawable();
    LobbyItem *temp;

//    int player_count = reply[1];
//    int lobby_status;
//    int player_id;
//    char player_name[24];
//    int id_position = 2;
//
//    for (int i = 0; i < player_count; i++) {
//        player_id = reply[id_position + (25 * i)];
//        lobby_status = reply[id_position + 23 + (25 * i)];
//        memmove(player_name, reply[id_position + 1 + (25 * i)], 23);
//
//        player_name[23] = 0;
//
//        temp = create_lobby_item(player_id, lobby_status, player_name);
//        push_lobby_item(lobbydrawable, temp);
//    }


    int player_count;
    int offset = 1;
    memset(&player_count, reply + offset, 1);
    offset += 1;
    int player_id;
    char* name = malloc(24);
    int status;
    int i;

    for (i = 0; i < player_count; i++) {
        memset(&player_id, reply + offset, 1);
        offset += 1;
        memmove(name, reply + offset, 23);
        name[24] = 0;
        offset += 23;
        memset(&status, reply + offset, 1);
        offset +=1;

        temp = create_lobby_item(player_id, status, name);
        push_lobby_item(lobbydrawable, temp);
        bzero(name, 24);
    }

    DrawNode *drawable = create_draw_node(DRAW_LOBBY, lobbydrawable);
    push_drawable_node(drawable);
}

void draw_lobby(LobbyDrawable *drawable) {
    int player_count = drawable->size;
    mvwprintw(lobby_window, 0, 0, "Player count: %d \n", player_count);

    LobbyItem *temp = drawable->head;
    int i = 1;

    while (temp != NULL) {
        mvwprintw(lobby_window, i, 0, "Player (ID %d ) %s status: %d",
                  temp->player_id,
                  temp->name,
                  temp->status);

        temp = temp->next;
        i ++;
    }
}
