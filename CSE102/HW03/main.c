#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

int get_location(int n)
{
	return (rand() % n); //returns random value between 0 and n(height or width of the map)
}

int check_status(int px, int py, int dx, int dy)
{
    if (px == dx && py == dy) // if the locations are same returns 1
        return (1);
    return (0);               //else 0
}

void draw_map(int n, int px, int py, int dx, int dy)
{
    int x;
    int i = 0;
    int j = 0;

    x = 2*n + 1;
    while (i < x)      //PRINTING
    {                  //TOP
        printf("-");   //OF
        i++;           //THE
    }                  //MAP
    printf("\n");
    i = 0;

    //EACH RUN OF THE LOOP, '|' MUST BE PRINTED
    //THEN C, D OR WHITESPACE MUST BE PRINTED
    //IF THE CURRENT COORDINATES(i,j) = px,py, 'C' is printed
    //IF THE CURRENT COORDINATES(i,j) = dx,dy, 'D' is printed
    //IF THE CURRENT COORDINATES = NEITHER PLAYER OR DOOR, ' ' is printed
    while (i < n)
    {

        j = 0;
        while (j < n + 1)
        {
            printf("|");
            if (i == py && j == px)
                printf("C");
            else if (i == dy && j == dx)
                printf("D");
            else
                printf(" ");
            j++;
        }
        printf("\n");
        i++;
    }


    i = 0;
    while (i < x)     //PRINTING
    {                 //BOTTOM
        printf("-");  //OF
        i++;          //THE
    }                 //MAP
}

void    play_the_game(int px, int py, int dx, int dy, int n)
{
    char ch;  //this refers to the move (UP, DOWN, LEFT, RIGHT)
    int  cnt; //this refers to the move counter

    cnt = 0;
    while (1)
    {
        printf("\nEnter a direction: ");
        scanf(" %c", &ch);
        while (getchar() != '\n');//this getchar clears the buffer

        //checking whether the input is valid or invalid
        if (ch != 'w' && ch != 's'
            && ch != 'a' && ch != 'd')
            printf("Invalid Key\n");

        switch(ch)
        {
            case UP:
                if (py - 1 != -1) //only, if the player is not 
                {                 //top of the map(if there is no wall above)
                    (py)--;       //it is allowed to move UP(py-1)
                    cnt++;        //incrementing counter by one, decrementing py by one
                }
                else
                    printf("Warning! There is a wall\n");
                break;

            case DOWN:
                if (py + 1 != n) //only, if the player is not
                {                //bottom of the map(if there is no wall under)
                    py += 1;     //it is allowed to move DOWN(py + 1)
                    cnt++;       //incrementing counter and py by one
                }
                else
                    printf("Warning! There is a wall\n");
                break;

            case LEFT:
                if (px - 1 != -1) //only, if the player is not
                {                 //on edge of the map(if there is no wall on left)
                    px -= 1;      //it is allowed to move LEFT(px - 1)
                    cnt++;        //incrementing counter aby one, decrementing px by one
                }
                else
                    printf("Warning! There is a wall\n");
                break;

            case RIGHT:
                if (px + 1 != n) //only if the player is not
                {                //on edge of the map(if there is no wall on right)
                    px += 1;     //it is allowed to move RIGHT(px + 1)
                    cnt++;       //incremeting counter and px by one
                }
                else
                    printf("Warning! There is a wall\n");
                break;
        }
        if (check_status(px, py, dx, dy) == 1) //if player and door at the same location, 
        {                                      //check status returns 1 and the ending protocols starts
            printf("The game is over\n");
            printf("'%d' moves were made during the game\n", cnt);
            printf("Returning back to the menu...\n\n\n");
            return ;
        }
        else                                   //if player does not reach the door
        {                                      //the new status of the map is printed
            draw_map(n, px, py, dx, dy);       //by draw map function
        }
    }
}

void    game_menu()
{
    int n;

    n = 1;
    //this wile contains the menu of the game
    //and its runs as long as the user choose 1 or 2
    //if user choose 1, the newgame protocols starts
    //if user choose 2, the description of the game is shown
    //if user choose 3, the program is terminated
    while (n == 1 || n == 2)
    {
        printf("Welcome to the 2D Puzzle Game!\n");
        printf("1. New Game\n");
        printf("2. Help\n");
        printf("3. Exit\n");
        scanf("%d", &n);
        
        if (n == 1)
        {
            int size;
            int	px; //x coordinate of player
            int	py; //y coordinate of player
            int dx; //x coordinate of door
            int	dy; //y coordinate of door

            srand(time(NULL)); //its for the rand function
            size = 0;
            while (size < 5 || size > 10)
            {
                printf("Enter the size the map: ");
                scanf("%d", &size);
                if (size < 5 || size > 10)
                    printf("Please enter a size between 5 and 10\n\n");
            }

            px = get_location(size);//getting x coordinate of player randomly
            py = get_location(size);//getting y coordinate of player randomly
            dx = get_location(size);//getting x coordinate of door randomly
            dy = get_location(size);//getting y coordinate of door randomly

            //if location of the player and door is same, the program
            //generate random door coordinates until they are different
            while (dx == px && dy == py)
            {
                dx = get_location(size);
                dy = get_location(size);
            }
            draw_map(size, px, py, dx, dy);
            play_the_game(px, py, dx, dy, size);
        }
        else if (n == 2)
        {
            printf("\n\nThe character is able to move one space in any of the four cardinal directions: up, down, left, and right.\n");
            printf("Diagonal moves are not allowed.\n");
            printf("You can not move through a wall.\n");
            printf("The game ends when the character reaches the door.\n\n\n\n");
        }
        else
        {
            printf("Goodbye! Have a Nice Day!\n\n");
            return ;
        }
    }

}

int main()
{
    game_menu();
    return (0);
}

