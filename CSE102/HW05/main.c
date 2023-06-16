#include <stdio.h>
#include <math.h>

typedef enum e_color
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    ORANGE
}Color;

/*
***********************************
*********PART1 FUNCTIONS***********
***********************************
*/

//This function converts lower case to uppercase
char to_upper(char ch)
{
    if (ch <= 'z' && ch >= 'a')
    {
        ch -= 32;
    }
    return (ch);
}

//This function fill the array with 0
void fill_arr(int arr[])
{
    int i;

    i = -1;
    while (++i < 26)
        arr[i] = 0;
}

//This function reads from file and
//store the letter frequency in array
void read_from_file(FILE *fp, int arr[])
{
    char ch;

    ch = fgetc(fp);
    while (ch != EOF)
    {
        if ((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A'))
        {
            ch = to_upper(ch);
            arr[ch - 65]++;
        }
        ch = fgetc(fp);
    }
}

//This functiın prints each index
//of array that stores letter frequency
void print_letter_freq(int arr[])
{
    int i;

    i = -1;
    printf("\nLetter Frequency:\n");
    while (++i < 26)
        printf("%c: %d\n", i + 65, arr[i]);
}

void part1()
{
    FILE *fp;
    char str[100];
    int  arr[26];  //an array for storing counts

    printf("Enter the file name: ");
    scanf("%s", str);
    fp = fopen(str, "r");
    if (!fp)
    {
        printf("There is no file as %s\n", str);
        return ;
    }
    fill_arr(arr);
    read_from_file(fp, arr);
    print_letter_freq(arr);
    fclose(fp);
}

/*
***********************************
*********PART2 FUNCTIONS***********
***********************************
*/


//this function fill the vector array based on given color
//for ex: color RED, vector [1, 0, 0]
void fill_vector(Color color, double vector[3])
{
    switch (color)
    {
        case RED:
            vector[0] = 1;
            break;
        case GREEN:
            vector[1] = 1;
            break;
        case BLUE:
            vector[2] = 1;
            break;
        case YELLOW:
            vector[0] = 0.5;
            vector[1] = 0.5;
            break;
        case ORANGE:
            vector[0] = 0.5;
            vector[1] = 0.4;
            vector[2] = 0.2;
            break;
    }
}

//this function mixes the given colors and calculates the closest distance
//returns the closest distance color as a result
Color color_distance(Color color1, Color color2)
{
    float distance;
    int i = 0; //loop index
    int res = 0; //it is index of all_color_vector for ex res = 0 indicates that color RED
    float tmp = 0; //temporary distance
    double all_color_vector[5][3] = {{1,0,0},{0,1,0},{0,0,1},{0.5,0.5,0},{0.5,0.4,0.2}};
    double vector1[3] = {0, 0, 0}; //color1 length
    double vector2[3] = {0, 0, 0}; //color2 length
    double mixedvector[3];

    fill_vector(color1, vector1); //filling vector1 based on color1
    fill_vector(color2, vector2); //filling vector2 based on color2

    //mixing colors
    mixedvector[0] = (vector1[0] + vector2[0]) / 2;
    mixedvector[1] = (vector1[1] + vector2[1]) / 2;
    mixedvector[2] = (vector1[2] + vector2[2]) / 2;
    distance = sqrt(pow((mixedvector[0]-all_color_vector[i][0]), 2)
                    +pow((mixedvector[1]-all_color_vector[i][1]), 2)
                    +pow((mixedvector[2]-all_color_vector[i][2]), 2));
    for (i = 1; i < 5; i++)
    {
        tmp = sqrt(pow((mixedvector[0]-all_color_vector[i][0]), 2)
                    +pow((mixedvector[1]-all_color_vector[i][1]), 2)
                    +pow((mixedvector[2]-all_color_vector[i][2]), 2));
        if (tmp < distance)
        {
            res = i;
            distance = tmp;
        }
    }
    switch (res)
    {
        case 0:
            return (RED);
            break;
        case 1:
            return (GREEN);
            break;
        case 2:
            return (BLUE);
            break;
        case 3:
            return (YELLOW);
            break;
        case 4:
            return (ORANGE);
            break;
    }
}

//this function calculate the distance and returns the color based on that distance
Color colorMixer(Color var1, Color var2, Color (*color_distance)(Color, Color))
{
    Color mixed_color;

    mixed_color = color_distance(var1, var2);
    return (mixed_color);
}

//this function enumerate the color based on the entered char
Color enumerate_color(char ch)
{
    Color color;
    switch (ch)
    {
        case 'r':
            color = RED;
            break;
        case 'g':
            color = GREEN;
            break;
        case 'b':
            color = BLUE;
            break;
        case 'y':
            color = YELLOW;
            break;
        case 'o':
            color = ORANGE;
            break;
        default:
            printf("INVALID INPUT\n");
            return (-1);
    }
    return (color);
}

void part2()
{
    char c1;
    char c2;
    Color color1;
    Color color2;
    Color mixed_color;

    //scanning and validating inputs
    printf("Enter Color 1 (r,g,b,y,o): ");
    scanf(" %c", &c1);
    color1 = enumerate_color(c1);
    if (color1 == -1)
        return ;
    printf("Enter Color 2 (r,g,b,y,o): ");
    scanf(" %c", &c2);
    color2 = enumerate_color(c2);
    if (color2 == -1)
        return ;

    mixed_color = colorMixer(color1, color2, color_distance);
    switch (mixed_color)
    {
        case RED:
            printf("Mixed Color: RED [1, 0, 0]");
            break;
        
        case GREEN:
            printf("Mixed Color: GREEN [0, 1, 0]");
            break;

        case BLUE:
            printf("Mixed Color: BLUE [0, 0, 1]");
            break;

        case YELLOW:
            printf("Mixed Color: YELLOW [0.5, 0.5, 0]");
            break;

        case ORANGE:
            printf("Mixed Color: ORANGE [0.5, 0.4, 0.2]");
            break;
    }
}

/*
***********************************
*********PART3 FUNCTIONS***********
***********************************
*/

//this function fill the board with '0'
void fill_board(char board[3][3])
{
    int i;
    int j;

    i = 0;
    while (i < 3)
    {
        j = 0;
        while (j < 3)
        {
            board[i][j] = 0;
            j++;
        }
        i++;
    }
}

//this function print the board
void print_board(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 'O' || board[i][j] == 'X')
                printf("%c ", board[i][j]);
            else
                printf("_ ");
        }
        printf("\n");
    }
}

//this function check if there is a row
//that its elements are the same (win case)
int check_horizontally(char board[3][3])
{
    if ((board[0][0] == board[0][1]) && (board[0][1] == board[0][2]))
    {
        if(board[0][0] == 'X')
            return (1);
        else if (board[0][0] == 'O')
            return (2);
    }
    if ((board[1][0] == board[1][1]) && (board[1][1] == board[1][2]))
    {
        if(board[1][0] == 'X')
            return (1);
        else if (board[1][0] == 'O')
            return (2);
    }
    if ((board[2][0] == board[2][1]) && (board[2][1] == board[2][2]))
    {
        if(board[2][0] == 'X')
            return (1);
        else if (board[2][0] == 'O')
            return (2);
    }
    return (0);
}

//this function check if there is a column
//that its elements are the same (win case)
int check_vertically(char board[3][3])
{
    if ((board[0][0] == board[1][0]) && (board[1][0] == board[2][0]))
    {
        if(board[0][0] == 'X')
            return (1);
        else if (board[0][0] == 'O')
            return (2);
    }
    if ((board[0][1] == board[1][1]) && (board[1][1] == board[2][1]))
    {
        if (board[0][1] == 'X')
            return (1);
        else if (board[0][1] == 'O')
            return (2);
    }
    if ((board[0][2] == board[1][2]) && (board[1][2] == board[2][2]))
    {
        if (board[0][2] == 'X')
            return (1);
        else if (board[0][2] == 'O')
            return (2);
    }
    return (0);
}

//this function checks the board diagonally
//if there are same elements diagonally it is win
int check_diagonally(char board[3][3])
{
    if (((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]))
        || ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0])))
    {
        if (board[1][1] == 'X')
            return (1);
        else if (board[1][1] == 'O')
            return (2);
    }
    return (0);
}

int check_winner(char board[3][3])
{
    int flag;

    flag = check_horizontally(board);
    if (flag != 0)
        return (flag);
    flag = check_vertically(board);
    if (flag != 0)
        return (flag);
    flag = check_diagonally(board);
    if (flag != 0)
        return (flag);
    return (-1);
}

//this function checks the board
//to determine win or tie
int check_board(char board[3][3])
{
    int i;
    int j;
    int flag;

    i = 0;
    flag = check_winner(board);
    if (flag != -1)
        return (flag);
    while (i < 3)
    {
        j = 0;
        while (j < 3)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return (-1); //indicates that the board is not full
            j++;
        }
        i++;
    }
    return (0);// indicates that its a tie
}

//this function checks whether the input is valid or not
int validate_input(int row, int col, char board[3][3])
{
    //if the position is already filled return (0)
    if (board[row][col] == 'O' || board[row][col] == 'X')
        return (0);
    //if the position is not inside the board return (0)
    if ((row > 2 || row < 0) || (col > 2 || col < 0))
        return (0);
    return (1);
}

//this function scans move, validates input, checks winner
void game_play(char board[3][3])
{
    int i = -1;
    int turn = 0;
    int flag;
    int row;
    int col;

    while (i == -1)
    {
        flag = 0;

        //CHECKING IF THE PLAYER 1 TURN
        if (turn % 2 == 0)
        {
            while (flag == 0)
            {
                printf("Player 1 (X), enter your move (row, col): ");
                scanf("%d %d", &row, &col); //scanning row col
                flag = validate_input(row, col, board); //validating input
                if (flag == 0)
                    printf("\n-> INVALID INPUT, ENTER AGAIN <-\n");
            }
            if (flag == 1) //if the move is valid, do it
                board[row][col] = 'X';
        }
        //CHECKING IF THE PLAYER 2 TURN
        else
        {
            while (flag == 0)
            {
                printf("Player 2 (O), enter your move (row, col): ");
                scanf("%d %d", &row, &col); //scanning row col
                flag = validate_input(row, col, board); //validating input
                if (flag == 0)
                    printf("\n-> INVALID INPUT, ENTER AGAIN <-\n");
            }
            if (flag == 1) //if the move is valid, do it
                board[row][col] = 'O';
        }
        turn++;
        print_board(board);
        printf("\n");
        i = check_board(board); //check whether its tie or win or not
        if (i == 2)
            printf("Player 2 (O) wins!");
        else if(i == 1)
            printf("Player 1 (X) wins!");
        else if (i == 0)
            printf("It's a tie");
    }


}

void part3()
{
    char board[3][3];
    char ch = 'Y';
    while (ch == 'Y')
    {
        fill_board(board);
        game_play(board);
        printf("\nPlay Another Game (Y) or Exit (N): ");
        scanf(" %c", &ch);
    }
}

int main()
{
    part1();
    printf("\n\n--> PART 2 <--\n\n");
    part2();
    printf("\n\n--> PART 3 <--\n\n");
    part3();
    return (0);
}