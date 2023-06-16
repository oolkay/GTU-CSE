#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

typedef struct board
{
    int board[3][3];
    int record;
}t_board;

//checks whether the board is solvable or not
int is_solvable(t_board board)
{
    int tmp_arr[9];
    int i = -1, j, cnt = 0;

    //making board linear in order to check if it is solvable
    while (++i < 9)
        tmp_arr[i] = board.board[i/3][i%3];

    i = 0;
    while (i < 8)
    {
        j = i + 1;
        while (j < 9)
        {
            if (tmp_arr[j] < tmp_arr[i] && (tmp_arr[j] > 0 && tmp_arr[i] > 0))
                cnt++;
            j++;
        }
        i++;
    }
    if (cnt % 2 == 0)
        return (1);
    return (0);
}

//finds the position of empty place(0)
//returns x y coordinates
void find_empty(t_board board, int *i, int *j)
{
    for (*i = 0; *i < 3; (*i)++)
        for (*j = 0; *j < 3; (*j)++)
            if (board.board[*i][*j] == 0)
                return ;
}

//prints the best score to the shell
void show_record(t_board board)
{
    int record = 0;
    char str[12];
    int i = 6;
    FILE *rec = fopen("record.txt", "r+");
    fscanf(rec, "%s", str);
    //scanned RECORD=<NBR>, assigning <NBR> to (int)record
    while (str[++i] != '\0')
        record = record * 10 + (str[i] - 48);
    printf("\n\n#The best score is: %d#\n\n", record);
    fclose(rec);
}

int check_dup(t_board board, int nbr)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (nbr == board.board[i][j])
                return (0);
    return (1);
}

//initialize the board
void init_board(t_board *board)
{
    char str[12];
    int record = 0, i = 6, j = 0, nbr = 0;
    
    //scanning the best score from record.txt
    FILE *rec = fopen("record.txt", "r+");
    fscanf(rec, "%s", str);
    //scanned RECORD=<NBR>, assigning <NBR> to (int)record
    while (str[++i] != '\0')
        record = record * 10 + str[i] - 48;

    for (i = 0; i < 9; i++)
        board->board[i/3][i%3] = -1;

    i = 0;
    while (i < 3)
    {
        j = 0;
        while (j < 3)
        {
            nbr = rand() % 9;
            if (check_dup(*board, nbr) == 1)
            {
                board->board[i][j] = nbr;
                j++;
            }
        }
        i++;
    }
    board->record = record;
    fclose(rec);
}

//this function
//1. checks whether the move is valid or not
//2. if it is valid applies it, else warns the player
int apply_move(t_board *board, int nbr, int *empty_x, int *empty_y, char direction)
{
    //swap the nbr and empty(0) cell
    switch (direction)
    {
        case 'R':
            board->board[*empty_x][*empty_y] = nbr;
            board->board[*empty_x][*empty_y - 1] = 0;
            (*empty_y) = *empty_y - 1;
            break;
        case 'L':
            board->board[*empty_x][*empty_y] = nbr;
            board->board[*empty_x][*empty_y + 1] = 0;
            (*empty_y) = *empty_y + 1;
            break;
        case 'U':
            board->board[*empty_x][*empty_y] = nbr;
            board->board[*empty_x + 1][*empty_y] = 0;
            (*empty_x) = *empty_x + 1;
            break;
        case 'D':
            board->board[*empty_x][*empty_y] = nbr;
            board->board[*empty_x - 1][*empty_y] = 0;
            (*empty_x) = *empty_x - 1;
            break;
    }
}

//this function
//1. prints the board to the board.txt
//2. prints the board to the terminal
void print_board(t_board board)
{
    FILE *fp = fopen("board.txt", "a");
    for (int j = 0; j < 3; j++)
    {
        if (j == 0)
            printf("\n\n");
        for (int k = 0; k < 3; k++)
        {
            printf("%d ", board.board[j][k]);
            fprintf(fp, "%d ",board.board[j][k]);
        }
        printf("\n");
        fprintf(fp, "\n");
    }
    printf("\n");
    fprintf(fp,"\n");
    fclose(fp);


}

//this function checks if the user finished the game
int check_win(t_board board)
{
    if (board.board[0][0]== 1 && board.board[0][1] == 2 && board.board[0][2] == 3
        && board.board[1][0] == 4 && board.board[1][1] == 5 && board.board[1][2] == 6
            && board.board[2][0] == 7 && board.board[2][1] == 8 && board.board[2][2] == 0)
                return (1);
    return (0);
}


//this function validates the move which was scanned from user
//if it is valid returns 1, else returns 0
int validate_user_move(t_board board, int nbr, char direction, int empty_x, int empty_y)
{
    if ((nbr <= 0 || nbr > 8) //if the given number is not valid
        || (direction != 'R' && direction != 'L' //if the direction is not valid
            && direction != 'U' && direction != 'D'))
                return (0);
    switch(direction)
    {
        case 'R':
            if (nbr == board.board[empty_x][empty_y - 1]) //checks left cell of the empty cell, if it is equal to nbr it is valid
                return (1);
            break;
        case 'L':
            if (nbr == board.board[empty_x][empty_y + 1]) //checks right cell of the empty cell, if it is equal to nbr it is valid
                return (1);
            break;
        case 'U':
            if (nbr == board.board[empty_x + 1][empty_y]) //checks upper cell of the empty cell, if it is equal to nbr it is valid
                return (1);
            break;
        case 'D':
            if (nbr == board.board[empty_x - 1][empty_y]) //checks lower cell of the empty cell, if it is equal to nbr it is valid
                return (1);
            break;
        default:
            return (0);
    }
    return (0);
}

//this function initialize the board by init_board()
//prints the board each loop by print_board()
//scans the move from user, and applies it by apply_move()
//checks the board whether the user finished the game or not check_win()
int user_play(t_board *board)
{
    //initialize the board and check if it is solvable
    init_board(board);
    while (is_solvable(*board) == 0)
        init_board(board);
    print_board(*board);

    int x,y;
    char move[4];
    int nbr, score = 0, cnt = 0, flag = 0;
    char direction;

    find_empty(*board, &x, &y);
    flag = check_win(*board);
    //this while runs until the puzzle is solved
    //scans number and direction from user every run
    //applies the move
    while (flag == 0)
    {
        printf("Enter the number and direction(for ex: 2-R): ");
        scanf("%s", move);
        nbr = move[0] - 48;
        direction = move[2];
        if (validate_user_move(*board, nbr, direction,x,y) == 1)
        {
            apply_move(board, nbr, &x, &y, direction);
            cnt++;
            print_board(*board);
        }
        else
            printf("\n-->INVALID MOVE<--\n\n");
        flag = check_win(*board);
    }
    if (flag == 1)//the win scneario
    {
        score = 1000 - 10*cnt;
        printf("Congrats! You finished the game\n\n");
        printf("Total number of moves: %d\n", cnt);
        printf("Your score: %d\n",score);
        if (score > board->record)
        {
            board->record = score;
            FILE *rec = fopen("record.txt", "w+");
            fprintf(rec,"RECORD=%d", score);
            fclose(rec);
        }
    }
}

// prints the board each loop by print_board()
// picks random legal move, and applies it by apply_move()
// checks the board whether the PC finished the game or not check_win()
int auto_finish(t_board *board, int *cnt, int *i, int *j, char *prev)
{
    int score = 0, flag = 0;
    char moves[5] = {'R','L','U','D'}; //directions
    int indx = rand() % 4;
    char direction = moves[indx];
    flag = check_win(*board);
    if (flag == 1)//if flags equals 1 that means the puzzle was solved by computer
    {
        score = 1000 - 10*(*cnt);//calculating the score
        printf("Computer finished the game\n\n");
        printf("Total number of computer moves: %d\n", *cnt);
        return (1);
    }
    else//if the puzzle is not solved yet
    {
        //this while choose legal move randomly
        while (direction == *prev || (*i == 0 && direction == 'D')
                || (*i == 2 && direction == 'U') || (*j == 0 && direction == 'R')
                    || (*j == 2 && direction == 'L'))
        {
            indx = rand() % 4;
            direction = moves[indx];
        }
        if (direction == 'R')
        {
            apply_move(board, board->board[*i][*j-1], i, j, direction);
            printf("Computer Move: %d-%c", board->board[*i][*j+1], direction);
            (*cnt)++;
            *prev = 'L';
        }
        else if (direction == 'L')
        {
            apply_move(board, board->board[*i][*j+1], i, j, direction);
            printf("Computer Move: %d-%c", board->board[*i][*j-1], direction);
            (*cnt)++;
            *prev = 'R';
        }
        else if (direction == 'D')
        {
            apply_move(board, board->board[*i-1][*j], i, j, direction);
            printf("Computer Move: %d-%c", board->board[*i+1][*j], direction);
            (*cnt)++;
            *prev = 'U';
        }
        else if (direction == 'U')
        {
            apply_move(board, board->board[*i+1][*j], i, j, direction);
            printf("Computer Move: %d-%c", board->board[*i-1][*j], direction);
            (*cnt)++;
            *prev = 'D';
        }
        print_board(*board);
        //every 20.000move in order to clear the stack, i terminate the recursive
        if (*cnt % 20000 == 0)
            return (0);
        auto_finish(board, cnt, i, j, prev);
    }
}

void menu()
{
    int i = 1;
    t_board board;

    FILE *fp;

    while (i == 1 || i == 2 || i == 3)
    {
        printf("\n****************************\n");
        printf("1)Play game as a user      *\n");
        printf("2)Finish the game with PC  *\n");
        printf("3)Show the best score      *\n");
        printf("4)Exit                     *\n");
        printf("****************************\n");
        printf("Select an option to continue: ");
        scanf("%d",&i);
        switch(i)
        {
            case 1://USER PLAY
                //open or clear the file
                fp = fopen("board.txt", "w");
                fclose(fp);
                user_play(&board);
                break;
            case 2://AUTO FINISH
                //open or clear the file
                fp = fopen("board.txt", "w");
                fclose(fp);

                int i=0,j=0,cnt=0;
                char prev = 0;//previous move. It s preventing the L-R-L-R... OR U-D-U-D... LOOP

                init_board(&board);
                //initialize board until finds solvable
                while (is_solvable(board) == 0)
                    init_board(&board);

                find_empty(board, &i, &j);

                //auto_finish function finish the game recursively, but due to segmentation
                //fault i had to clear the stack so every 20.000 move the recursive ends then starts again
                //in other words i clear the stack every 20.000 move
                while(auto_finish(&board, &cnt, &i, &j, &prev) == 0);
                break;
            case 3://SHOW RECORD
                show_record(board);
                break;
            case 4://EXIT
                return ;
        }
    }
}

int main()
{
    srand(time(NULL));
    menu();
}