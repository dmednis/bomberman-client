#include <ncurses.h>



#ifndef BOMBERMAN_CLIENT_DRAWING_H
#define BOMBERMAN_CLIENT_DRAWING_H

typedef struct DrawNode {
    int type;
    void *data;
    struct DrawNode *next;
    struct DrawNode *prev;
} DrawNode;

typedef struct {
    DrawNode *head;
    DrawNode *tail;
    int size;
} DrawQueue;

typedef struct LobbyItem {
    int player_id;
    int status;
    char *name;
    struct LobbyItem *next;
    struct LobbyItem *prev;
} LobbyItem;

typedef struct LobbyDrawable {
    LobbyItem *head;
    LobbyItem *tail;
    int size;
} LobbyDrawable;

void close_window(WINDOW *window);
void *draw_callback(void *arg);
void queue_lobby_info(unsigned char *replay);
void draw(DrawNode *drawable);
void draw_lobby(LobbyDrawable *drawable);

DrawQueue *create_draw_queue();
DrawNode *create_draw_node(int draw_node_type, void *draw_node_data);
DrawNode *push_drawable_node(DrawNode *drawNode);
DrawNode *pop_node();

LobbyDrawable *create_lobby_drawable();
LobbyItem *create_lobby_item(int id, int status, char *name);
LobbyItem *push_lobby_item(LobbyDrawable *list, LobbyItem *lobby_item);
void dispose_lobby_drawable(LobbyDrawable *list);

#endif //BOMBERMAN_CLIENT_DRAWING_H
