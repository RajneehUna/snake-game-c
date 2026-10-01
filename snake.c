// Headers
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

// Constants
#define WIDTH 20
#define HEIGHT 20
#define MAX_TAIL 100

// Global Variables
int gameOver, score;
int x, y, foodX, foodY, tailX[MAX_TAIL], tailY[MAX_TAIL], nTail;

// Enum for direction
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum Direction dir;

// Function Prototypes
void setup();
void draw();
void input();
void logic();
void generateFood();

// Helper functions for smooth rendering (prevents screen scrolling/flicker)
void SetCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void HideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

// Main Function
int main() {
    srand((unsigned int)time(NULL)); // Seed random food positions
    system("cls");                   // Clear screen once at start
    HideCursor();                    // Hide blinking console cursor

    setup();

    while (!gameOver)
    {
        draw();
        input();
        logic();

        Sleep(100);
    }

    system("cls"); // Clear screen for clean Game Over layout
    printf("================================\n");
    printf("           GAME OVER\n");
    printf("================================\n");
    printf("Final Score: %d\n", score);
    printf("\nPress any key to exit...");

    _getch();
    return 0;
}

// Function Definitions
void setup()
{
    gameOver = 0;
    score = 0;
    nTail = 0; // Fixed: Reset tail length to 0

    x = WIDTH / 2;
    y = HEIGHT / 2;

    dir = STOP;

    generateFood();
}

// Draw Function
void draw()
{
    SetCursorPosition(0, 0); // Fixed: Reposition cursor instead of system("cls")

    printf("Score: %d                   \n", score);
    printf("Use Arrow Keys to Move | Press ESC to Exit\n");

    // Top Border
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");

    printf("\n");

    // Grid rendering
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0)
                printf("#"); // Left Wall

            if (i == y && j == x)
                printf("O"); // Snake Head
            else if (i == foodY && j == foodX)
                printf("F"); // Food
            else
            {
                // Fixed: Added Tail Loop to print tail segments
                int printTail = 0;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        printf("o"); // Snake Tail Segment
                        printTail = 1;
                        break;
                    }
                }
                if (!printTail)
                    printf(" "); // Empty space
            }

            if (j == WIDTH - 1)
                printf("#"); // Right Wall
        }

        printf("\n");
    }

    // Bottom Border
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");

    printf("\n");
}

// Input Function
void input()
{
    if (_kbhit())
    {
        int key = _getch();

        // Fixed: Added ESC key detection (ASCII 27)
        if (key == 27)
        {
            gameOver = 1;
        }
        else if (key == 224 || key == 0)
        {
            key = _getch();

            switch (key)
            {
            case 75:   // Left Arrow
                if (dir != RIGHT)
                    dir = LEFT;
                break;

            case 77:   // Right Arrow
                if (dir != LEFT)
                    dir = RIGHT;
                break;

            case 72:   // Up Arrow
                if (dir != DOWN)
                    dir = UP;
                break;

            case 80:   // Down Arrow
                if (dir != UP)
                    dir = DOWN;
                break;
            }
        }
    }
}

// Logic Function
void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];

    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;

    case RIGHT:
        x++;
        break;

    case UP:
        y--;
        break;

    case DOWN:
        y++;
        break;

    default:
        break;
    }

    // Wall Collision
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
    {
        gameOver = 1;
    }

    // Food Collision
    if (x == foodX && y == foodY)
    {
        score += 10;

        if (nTail < MAX_TAIL)
            nTail++;

        generateFood();
    }

    // Self Collision
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = 1;
        }
    }
}

// Generate Food Function
void generateFood()
{
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
}