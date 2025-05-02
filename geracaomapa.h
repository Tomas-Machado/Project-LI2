#ifndef MAPA_H
#define MAPA_H

#include "state.h"

#define PLAYER   '@'
#define PAREDE   '#'
#define CHAO     '.'
#define MOB      'M'

#define ESPADA   'E'
#define ESCUDO   'S'
#define TRAP     'T'

void initialize_map();
void add_borders();
void add_caves();
void smooth_map();
void print_map();
void generate_map();


#endif
