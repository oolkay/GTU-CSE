#include "utils.h"

void update(Block ***board, s_snake *snake, int cnt, int *obstacle_cnt)
{
    int len = snake->snake_len, i = 0 , j = 0, flag = 0, obs = 0, tmp = 0, h = 0, z = 0;
    Point bait;
    Point obstacle;
    
    //CHECKING WHETHER THE SNAKE EAT BAIT OR HIT OBSTACLE
    //IF THE SNAKE EAT BAIT, UPDATING THE SNAKE BODY
    //IF THE SNAKE HIT OBSTACLE, UPDATING THE OBSTACLE
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (board[i][j][0].type == 'b' && snake->body[0].col == j && snake->body[0].row == i)
            {
                snake->snake_len++;//UPDATING THE SNAKE'S LENGTH
                len = snake->snake_len;//
                snake->body = (Point *)realloc(snake->body, sizeof(Point) * (len));//REALLOCATING MEMORY FOR THE NEW POINT
                switch (snake->last_move)//ASSIGNING THE NEW POINT'S COORDINATES
                {
                    case 'd':
                        snake->body[(len) - 1].col = j - 1; 
                        snake->body[(len) - 1].row = i; 
                        break;
                    case 'a':
                        snake->body[(len) - 1].col = j + 1; 
                        snake->body[(len) - 1].row = i; 
                        break;
                    case 'u':
                        snake->body[(len) - 1].col = j; 
                        snake->body[(len) - 1].row = i + 1; 
                        break;
                    case 's':
                        snake->body[(len) - 1].col = j; 
                        snake->body[(len) - 1].row = i - 1; 
                        break;
                }
                board[i][j][0].type = 'e';//ASSIGNING 'e' TO THE PREVIOUS POINT
                board[i][j][0].value = 0;//ASSIGNING '0' TO THE PREVIOUS POINT
                flag = 1;
            }

            else if(board[i][j][0].type == 'o' && snake->body[0].col == j//IF THE SNAKE'S HEAD IS ON AN OBSTACLE
                && snake->body[0].row == i && snake->snake_len >= board[i][j][0].value)//IF THE SNAKE'S LENGTH IS BIGGER THAN THE OBSTACLE'S VALUE
            {
                board[i][j][0].type = 'e';//ASSIGNING 'e' TO THE PREVIOUS POINT
                board[i][j][0].value = 0;// 
                (*obstacle_cnt)--;//DECREASING THE OBSTACLE'S COUNTER
            }
        }
    }

    //UPDATING THE SNAKE'S "BODY" ("HEAD" IS UPDATED IN MOVE FUNCTION AS THE "PDF" SAID)
    if (snake->snake_len >= 2)
    {
        i = snake->snake_len -1;
        while (i > 0)//UPDATING THE SNAKE'S "BODY"
        {
            snake->body[i].col = snake->body[i - 1].col;
            snake->body[i].row = snake->body[i - 1].row;
            i--;
        }
        switch (snake->last_move)//since ı have moved snake's head on "move" function, ı have to update the first point after the head
        {//according to the last move
            case 'w':
                snake->body[1].row = snake->body[0].row + 1;
                break;
            case 's':
                snake->body[1].row = snake->body[0].row - 1;
                break;
            case 'd':
                snake->body[1].col = snake->body[0].col - 1;
                break;
            case 'a':
                snake->body[1].col = snake->body[0].col + 1;
                break;
        }
    }

    //IF THE SNAKE ATE BAIT, ADDING A BAIT TO THE BOARD
    if (flag == 1)
    {
        i = 0;
        bait.col = rand() % 10;
        bait.row = rand() % 10;
        while (i < snake->snake_len)
        {
            if (bait.col == snake->body[i].col && bait.row == snake->body[i].row)
            {
                bait.col = rand() % 10;
                bait.row = rand() % 10;
                i = 0;
            }
            else
                i++;
        }
        board[bait.row][bait.col][0].type = 'b';
        board[bait.row][bait.col][0].value = 0;
    }
    //IF THERE ARE OBSTACLE LESS THAN 3, ADDING AN OBSTACLE TO THE BOARD EVERY 5 MOVE
    if (cnt % 5 == 0 && (*obstacle_cnt) < 3 && cnt != 0)
    {
        i = 0;
        obstacle.col = rand() % 10;
        obstacle.row = rand() % 10;
        while (i < snake->snake_len)
        {
            if (obstacle.col == snake->body[i].col && obstacle.row == snake->body[i].row)
            {
                obstacle.col = rand() % 10;
                obstacle.row = rand() % 10;
                i = 0;
            }
            else
                i++;
        }
        board[obstacle.row][obstacle.col][0].type = 'o';
        board[obstacle.row][obstacle.col][0].value = rand() % 9 + 1;
        (*obstacle_cnt)++;
    }
    //IF THERE ARE 3 OBSTACLES ON THE BOARD, UPDATING THE HEIGHT OF ONE OF THEM EVERY 5 MOVE
    else if(cnt % 5 == 0 && (*obstacle_cnt) == 3 && cnt != 0)
    {
        obs = rand() % 3 + 1;//randomly choosing an obstacle to upgrade its height/value
        for (i = 0; i < 10; i++)
        {
            for (j = 0; j < 10; j++)
            {
                if (board[i][j][0].type == 'o' && board[i][j][0].value < 9)
                    tmp++;
                if (tmp == obs)
                {
                    board[i][j][h].value = board[i][j][h].value + rand() % (9 - board[i][j][z].value) + 1;
                    return ;
                }
            }
        }
    }

}
//CHECKING THE STATUS OF THE GAME
int check_status(Block ***board, s_snake *snake)
{
    int i = 0;
    //CHECKING IF THE SNAKE HAS HIT THE WALL
    if (snake->body[0].row < 0 || snake->body[0].row > 9 || snake->body[0].col < 0 || snake->body[0].col > 9)
        return (1);

    //CHECKING IF THE SNAKE HAS HIT THE OBSTACLE, IF IT HIT THE OBSTACLE CHECKKING IF THE SNAKE'S LENGTH IS GREATER THAN THE OBSTACLE'S VALUE
    if (board[snake->body[0].row][snake->body[0].col][0].type == 'o'
        && board[snake->body[0].row][snake->body[0].col][0].value > snake->snake_len)
        return (1);
    
    //CHECKING IF THE SNAKE HIT ITSELF
    while (i < snake->snake_len)
    {
        if (i != 0 && snake->body[0].row == snake->body[i].row && snake->body[0].col == snake->body[i].col)
            return (1);
        i++;
    }
    return (0);
}

void move(s_snake *snake)
{
    char ch;
    int i;
    printf("\n\nEnter the move: ");
    scanf(" %c", &ch);

    //MOVING THE SNAKE'S HEAD
    switch(ch)
    {
        case 'w':
            snake->body[0].row--;
            snake->last_move = 'w';
            break;
        case 's':
            snake->body[0].row++;
            snake->last_move = 's';
            break;
        case 'd':
            snake->body[0].col++;
            snake->last_move = 'd';
            break;
        case 'a':
            snake->body[0].col--;
            snake->last_move = 'a';
            break;
        default :
            printf("Invalid move!\n");
            break;
    }
}

void play(Block ***board)
{
    s_snake snake;
    snake.body = (Point *)malloc(sizeof(Point) * 1);
    snake.snake_len = 1;
    int i = 0;
    int j = 0;
    int cnt = 0;
    int flag = 1;
    int obstacle_cnt = 1;
    snake.body[0].col = 0;
    snake.body[0].row = 0;
    draw_board(board, &snake);
    while (flag == 1)
    {
        move(&snake);
        if (check_status(board, &snake) == 1)
        {
            printf("Game Over!\n");
            flag = 0;
        }
        else
        {
            cnt++;
            update(board, &snake, cnt, &obstacle_cnt);
            draw_board(board, &snake);
        }
    }
    free(snake.body); //FREEING THE SNAKE'S BODY DUE TO MEMORY LEAK
}

//DRAWING THE BOARD
void draw_board(Block ***board, s_snake *snake)
{
    int i = -1;
    int j = 0;
    int k = 0;
    int flag = 1;
    while (++i < 22)
        printf("-");
    printf("\n");

    for (i = 0; i < 10; i++)
    {
        printf("|");
        for (j = 0; j < 10; j++)
        {
            flag = 1;
            k = 0;
            while (k < snake->snake_len)
            {
                if (k == 0 && snake->body[k].col == j && snake->body[k].row == i)//IF THE POINT IS THE SNAKE'S HEAD
                {
                    printf("O ");
                    flag = 0;
                }
                else if (k != 0 && snake->body[k].col == j && snake->body[k].row == i)//IF THE POINT IS THE SNAKE'S BODY
                {
                    printf("X ");
                    flag = 0;
                } 
                k++;
            }
            if (board[i][j][0].type == 'e' && flag == 1)//IF THE POINT IS EMPTY
                printf("  ");
            else if (board[i][j][0].type == 'o' && flag == 1)//IF THE POINT IS AN OBSTACLE
                printf("%d ", board[i][j][0].value);
            else if (board[i][j][0].type == 'b' && flag == 1)// IF THE POINT IS THE BAIT
                printf(". ");
        }
        printf("|");
        printf("\n");
    }
    i = -1;
    while (++i < 22)
        printf("-");
}

//Allocating the memory for each block of board
Block ***init_board()
{
    srand(time(NULL));
    int i = 0;
    int j = 0;
    Block ***board;
    Point bait;
    Point obstacle;
    int o_value;

    board = (Block ***)malloc(sizeof(Block **) * 10);
    while (i < 10)
    {
        board[i] = (Block **)malloc(sizeof(Block *) * 10);
        j = 0;
        while (j < 10)
        {
            board[i][j] = (Block *)malloc(sizeof(Block) * 9);
            board[i][j][0].type = 'e';
            board[i][j][0].value = 0;
            j++;
        }
        i++;
    }

    //INITIALIZING THE BAIT
    bait.col = rand() % 10;
    bait.row = rand() % 10;
    while (bait.col == 0 && bait.row == 0)
    {
        bait.col = rand() % 10;
        bait.row = rand() % 10;
    }

    //INITIALIZING THE OBSTACLE
    obstacle.col = rand() % 10;
    obstacle.row = rand() % 10;
    o_value = rand() % 9 + 1;
    while ((obstacle.col == 0 && obstacle.row == 0)
        && (obstacle.col == bait.col && obstacle.row == bait.row))
    {
        bait.col = rand() % 10;
        bait.row = rand() % 10;
    }

    //SETTING THE BAIT AND OBSTACLE IN THE BOARD
    board[bait.row][bait.col][0].type = 'b';
    board[bait.row][bait.col][0].value = 0;
    board[obstacle.row][obstacle.col][0].type = 'o';
    board[obstacle.row][obstacle.col][0].value = o_value;
    return (board);
}

int main()
{
    Block ***board = init_board();
    play(board);


    int i = 0;
    int j = 0;

    //FREEING THE BOARD'S MEMORY, STARTING FROM THE INSIDE (snake array was freed in play function)
    while (i < 10)
    {
        j = -1;
        while (++j < 10)
            free(board[i][j]);
        free(board[i]);
        i++;
    }
    free(board);

    return (0);
}
