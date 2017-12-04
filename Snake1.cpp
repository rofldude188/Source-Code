#include <iostream>
#include <thread>
#include <chrono>
#include <oled-exp.h>
#include <onion--i2c.h>
using namespace std;
//GOAL OF THIS ITERATION OF SNAKE GAME IS TO DISPLAY GAMEBOARD PROPERLY ON OMEGA
bool gameOver;
const int width = 100;
const int height = 50;
int xpos;
int ypos;
int foodX;
int foodY;
int score;
int snakeX[100];
int snakeY[100];
int snakeLength;
enum direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
direction dir;
int status;
void gameSetup()
{
    gameOver = false;
    dir = STOP;
    xpos = width / 2;
    ypos = height / 2;
    foodX = rand() % width;
    foodY = rand() % height;
    score = 0;
}
void drawBoard() //OLED expansion
{
	//set initial board state
	status = oledSetCursorByPixel(3, 63);
	status = oledWriteChar("o");
	for(int i = 0; i < 128; i++){
		status = oledSetCursorByPixel(0, i);
		status = oledWriteChar("#");
		status = oledSetCursorByPixel(7, i);
		status = oledWriteChar("#");
	}
	for(int i = 1; i < 7; i++){
		status = oledSetCursorByPixel(i, 0);
		status = oledWriteChar("#");
		status = oledSetCursorByPixel(i, 127);
		status = oledWriteChar("#");
	}
	/*
    for (int i = 0; i < width; i++)
    {
        cout << "#";
    }
    cout << endl;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width-2; j++)
        {
            if (j == 0)
            {
                cout << "#";
            }
            if (i == ypos && j == xpos)
            {
                cout << "O";
            }
            else if (i == foodY && j == foodX)
            {
                cout << "F";
            }
            else
            {
                bool print = false;
                for (int k = 0; k < snakeLength; k++)
                {
                    if (snakeX[k] == j && snakeY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                {
                    cout << " ";
                }
            }
            if (j == width - 3)
            {
                cout << "#";
            }
        }
        cout << endl;
    }
    
    for (int i = 0; i < width; i++)
    {
        cout << "#";
    }
    cout << endl;
    cout << "Current score: " << score << endl;
	*/
}
/*void gameInput() //switches
{
    char i;
    cin >> i;
        switch (i)
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
    }
}
void gameMechanics()
{
    int prevX = snakeX[0];
    int prevY = snakeY[0];
    int prevX2, prevY2;
    snakeX[0] = xpos;
    snakeY[0] = ypos;
    for (int i = 1; i < snakeLength; i++)
    {
        prevX2 = snakeX[i];
        prevY2 = snakeY[i];
        snakeX[i] = prevX;
        snakeY[i] = prevY;
        prevX = prevX2;
        prevY = prevY2;
    }
    switch (dir)
    {
        case LEFT:
            xpos--;
            break;
        case RIGHT:
            xpos++;
            break;
        case UP:
            ypos--;
            break;
        case DOWN:
            ypos++;
            break;
        default:
            break;
    }
    if (xpos > width-1 || xpos < 1 || ypos > height-1 || ypos < 1)
    {
        gameOver = true;
    }
    
    for (int i = 0; i < snakeLength; i++)
    {
        if (snakeX[i] == xpos && snakeY[i] == ypos){
            gameOver = true;
        }
    }

    if (xpos == foodX && ypos == foodY)
    {
        score += 10;
        foodX = rand() % width;
        foodY = rand() % height;
        snakeLength++;
    }
}*/
int main()
{
	int status = oledDriverInit();
	status = oledSetDisplayPower(1);
    gameSetup();
    while (!gameOver)
    {
        drawBoard();
        //gameInput();
        //gameMechanics();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if (gameOver)
    {
        cout << "GAME OVER!" << endl;
        cout << "SCORE: " << score << endl;
    }
    return 0;
}
