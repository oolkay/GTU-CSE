#ifndef UTILS_H
# define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

/*Point Struct*/
typedef struct s_point
{
    int row;
    int col;
}Point;

/*Block Struct*/
typedef struct s_block
{
    char type;
    int value;
}Block;

/*Snake Struct that contains Point struct*/
typedef struct snake
{
    Point *body;
    int snake_len;
    char last_move;

}s_snake;

/*PART 1-> INITIALIZE THE BOARD*/
Block ***init_board();

/*PART 2-> DRAW THE BOARD*/
void draw_board(Block ***board, s_snake *snake);

/*PART3-> GAME PLAY FUNCTIONS*/
void play(Block ***board);
void move(s_snake *snake);
int check_status(Block ***board, s_snake *snake);
void update(Block ***board, s_snake *snake, int cnt, int *obstacle_cnt);


#endif