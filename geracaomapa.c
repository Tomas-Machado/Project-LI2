#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "geracaomapa.h"
#include "state.h"
#include "globals.h"

char map[MAP_HEIGHT][MAP_WIDTH];

/*
?           Tomás Machado
! Todo o ficheiro foi feito por mim
*/

//todo Inicializa o mapa todo com o carater '.' de forma a que o mapa nao seja inicado com carateres aleatórios

void initialize_map() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map[y][x] = '.';
        }
    }
}


//todo Adiciona as paredes sem ter mais de 2 bordas
void add_borders() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (y < WALL_BORDER || y >= MAP_HEIGHT - WALL_BORDER ||
                x < WALL_BORDER || x >= MAP_WIDTH - WALL_BORDER) {
                map[y][x] = '#';
            }
        }
    }
}

//todo Adicionadas as cavernas com os 40% de ocupação por paredes
void add_caves() {
    int fill_percentage = 40;
    srand(time(NULL));
    int num_walls = MAP_HEIGHT * MAP_WIDTH * fill_percentage / 100;  //! fazer a determinação de quantas paredes serão adicionadas ao mapa com base na percentagem dada



    for (int i = 0; i < num_walls; i++) {
        int x = rand() % (MAP_WIDTH - 2) + 1;     //! O valor MAP_WIDTH - 2 é utilizado para garantir que as paredes não sejam adicionadas nas bordas do mapa.
        int y = rand() % (MAP_HEIGHT - 2) + 1;   //! O valor MAP_HEIGHT - 2 é utilizado para garantir que as paredes não sejam adicionadas nas bordas do mapa.
        map[y][x] = '#';                        //! Marca a posição como uma parede
    }

//! Algoritmo Automata
    for (int i = 0; i < 4; i++) {
        for (int y = 1; y < MAP_HEIGHT - 1; y++) {
            for (int x = 1; x < MAP_WIDTH - 1; x++) {
                int neighbor_wall_count = 0;
                for (int yy = y - 1; yy <= y + 1; yy++) {         //! yy representa as células vizinhas de y
                    for (int xx = x - 1; xx <= x + 1; xx++) {    //!  xx representa as células vizinhas de x
                        if (map[yy][xx] == '#' && (yy != y || xx != x)) { 
                            neighbor_wall_count++;              //! verificado se a posição (yy, xx) do mapa contém uma parede ('#'). Se essa condição for satisfeita e a posição não for a mesma que a posição atual (y, x)
                        }                                      //! Então aumenta-se o contador de células vizinhas
                    }
                }
                if (map[y][x] == '#') {
                    if (neighbor_wall_count < 3) {           //! Verificação de que se existir mais de 3 células parede, a próxima será um chão
                        map[y][x] = '.';
                    }
                }
                if (map [y][x]== '.') {
                    if (neighbor_wall_count > 4) {         //! Verificação de que se existir mais de 4 células chão, a próxima será uma parede
                        map[y][x] = '#';
                    }
                }
            }
        }
    }
}


//todo Torna o mapa mais suave
//todo Essas regras visam suavizar ainda mais as cavernas, removendo pequenas áreas de paredes isoladas e preenchendo pequenos espaços vazios.
//todo Esta funçaõ apenas itera 3 vezes para que o mapa não tenha um estilo muito sufocante
void smooth_map() {
    for (int i = 0; i < 3; i++) {
        for (int y = 1; y < MAP_HEIGHT - 1; y++) {
            for (int x = 1; x < MAP_WIDTH - 1; x++) { 
                int neighbor_wall_count = 0;
                for (int yy = y - 1; yy <= y + 1; yy++) {
                    for (int xx = x - 1; xx <= x + 1; xx++) {
                        if (map[yy][xx] == '#') {
                            neighbor_wall_count++;
                        }
                    }
                }
                if (map[y][x] == '#') {
                    if (neighbor_wall_count < 3) {
                        map[y][x] = '.';
                    }
                } else {
                    if (neighbor_wall_count > 4) {
                        map[y][x] = '#';
                    }
                }
            }
        }
    }
}


//todo Apresenta o mapa no ecrã
void print_map() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            printf("%c", map[y][x]);
        }
        printf("\n");
    }
}


//todo Função que compacta quase todas as funções incluidas no ficheiro para uma vizualização mais simplificada no ficheiro principal do jogo
void generate_map() {

    // Add the borders of the map
    add_borders();

    // Add caves
    add_caves();

    // Smooth map
    for (int i = 0; i < 4; i++) {
        smooth_map();
    }

    // Print map
    print_map();
}
