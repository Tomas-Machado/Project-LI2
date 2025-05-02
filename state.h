#ifndef _STATEH
#define _STATEH


typedef struct _STATE {
    int player_row;
    int player_col;
    int mob_row;
    int mob_col;
    bool mob_alive;
    int dx;
    int dy;
    int wall_border;
    int num_walls;
    int map_width;
    int map_height;
    int player_hp;
    int mob_hp;
    int player_shield;
    char **map;
} STATE;


typedef struct {
    char arms[5][20];
    int num_arms;
} Inventory;




#endif
