#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ugpio/ugpio.h>
#include <oled-exp.h>
#include <onion-i2c.h>


using namespace std;
bool x;
bool gameOver;
int value1, value2, value3, value4;
int rows, cols;
const int rowMax = 7;
const int colMax = 20;
int foodCol;
int foodRow;
int score;
int snakeX[100];
int snakeY[100];
int snakeLength;
enum direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
direction dir;
int status;

void gameSetup()
{
	for (int i = 0; i < 100; ++i){
		snakeX[i] = -1;
		snakeY[i] = -1;
	}
	snakeLength = 0;
	status = oledDriverInit();
	status = oledSetDisplayPower(1);
	x = false;
    gameOver = false;
    dir = STOP;
    score = 0;
	rows = rowMax/2;
	cols = colMax/2;
	foodRow = 3;
	foodCol = 5;
}

void drawBoard()
{	
    for (int i = 0; i < rowMax; ++i)
    {
        for (int j = 0; j < colMax; ++j)
        {
            if (i == rows && j == cols)
            {
                status = oledSetTextColumns();
				status = oledSetCursor(i,j);
				status|= oledWriteChar('O');
            }
			else if (i == foodRow && j == foodCol){
				status = oledSetTextColumns();
				status = oledSetCursor(i,j);
				status|= oledWriteChar('F');
			}
            else
            {
                bool print = false;
                for (int k = 0; k < snakeLength; k++)
                {
                    if (snakeX[k] == j && snakeY[k] == i)
                    {
                        status = oledSetTextColumns();
						status = oledSetCursor(i,j);
						status|= oledWriteChar('o');
                        print = true;
                    }
                }
                if (!print)
                {
                    status = oledSetTextColumns();
					status = oledSetCursor(i,j);
					status|= oledWriteChar('.');
                }
            }
        }
    }
}

int gameInput() //switches
{
	int i;
	int rq1,rq2,rq3,rq4; 
	int rv1,rv2,rv3,rv4;
	int gpio1, gpio2, gpio3, gpio4;


	/*if (argc < 2) {
		printf("Usage: gpioRead <gpio>\n\n");
		printf("Reads the input value of the specified GPIO pin once a second for 20 seconds\n");
		exit(-1);
	}*/

	gpio1=0;    //up
	gpio2=1;	//left
	gpio3=2;	//right
	gpio4=3;	//down
	//gpio = atoi(argv[1]);

	// check if gpio is already exported
	if ((rq1 = gpio_is_requested(gpio1)) < 0)
	{
		perror("gpio1_is_requested");
		return EXIT_FAILURE;
	}
	if ((rq2 = gpio_is_requested(gpio2)) < 0)
	{
	 	perror("gpio2_is_requested");
	 	return EXIT_FAILURE;
	}
	if ((rq3 = gpio_is_requested(gpio3)) < 0)
	{
	 	perror("gpio3_is_requested");
	 	return EXIT_FAILURE;
	}
	if ((rq4 = gpio_is_requested(gpio4)) < 0)
	{
	 	perror("gpio4_is_requested");
	 	return EXIT_FAILURE;
	}
	// export the gpio
	if (!rq1) {
		//printf("> exporting gpio1\n");
		if ((rv1 = gpio_request(gpio1, NULL)) < 0)
		{
			perror("gpio1_request");
			return EXIT_FAILURE;
		}
	}
	if (!rq2) {
	 	//printf("> exporting gpio2\n");
	 	if ((rv2 = gpio_request(gpio2, NULL)) < 0)
	 	{
	 		perror("gpio2_request");
	 		return EXIT_FAILURE;
	 	}
	}
	if (!rq3) {
	 	//printf("> exporting gpio3\n");
	 	if ((rv3 = gpio_request(gpio3, NULL)) < 0)
		{
			perror("gpio3_request");
	 		return EXIT_FAILURE;
		}
	}
	if (!rq4) {
	 	//printf("> exporting gpio4\n");
	 	if ((rv4 = gpio_request(gpio4, NULL)) < 0)
	 	{
	 		perror("gpio4_request");
	 		return EXIT_FAILURE;
	 	}
	}

	// set to input direction
	//printf("> setting to input\n");
	if ((rv1 = gpio_direction_input(gpio1)) < 0)
	{
		perror("gpio1_direction_input");
	}
	if ((rv2 = gpio_direction_input(gpio2)) < 0)
	{
	 	perror("gpio2_direction_input");
	}
	 if ((rv3 = gpio_direction_input(gpio3)) < 0)
	{
	 	perror("gpio3_direction_input");
	}
	 if ((rv4 = gpio_direction_input(gpio4)) < 0)
	{
	 	perror("gpio4_direction_input");
	}
	
	 //read the gpio 20 times
	/*printf("> begin reading GPIO%d\n",gpio1);
	printf("> begin reading GPIO%d\n",gpio2);
	printf("> begin reading GPIO%d\n",gpio3);
	printf("> begin reading GPIO%d\n",gpio4);*/
		
		// read the gpio
		value1 = gpio_get_value(gpio1);
		//printf("  > Read GPIO1%d: value '%d'\n", gpio1, value1);
		value2 = gpio_get_value(gpio2);
		//printf("  > Read GPIO2%d: value '%d'\n", gpio2, value2);
		value3 = gpio_get_value(gpio3);
		//printf("  > Read GPIO3%d: value '%d'\n", gpio3, value3);
		value4 = gpio_get_value(gpio4);
		//printf("  > Read GPIO4%d: value '%d'\n", gpio4, value4);
		// pause between each read
		//usleep(100000);

	// unexport the gpio
	if (!rq1) {
		//printf("> unexporting gpio1\n");
		if (gpio_free(gpio1) < 0)
		{
			perror("gpio1_free");
		}
	}
	if (!rq2) {
	 	//printf("> unexporting gpio2\n");
	 	if (gpio_free(gpio2) < 0)
	 	{
	 		perror("gpio2_free");
	 	}
	 }
	 if (!rq3) {
	 	//printf("> unexporting gpio3\n");
	 	if (gpio_free(gpio3) < 0)
	 	{
	 		perror("gpio3_free");
	 	}
	 }
	 if (!rq4) {
	 	//printf("> unexporting gpio4\n");
	 	if (gpio_free(gpio4) < 0)
	 	{
	 		perror("gpio4_free");
	 	}
	}
	
	if (value1 == 1){
		dir = UP;
	}
	else if (value2 == 1){
		dir = LEFT;
	}
	else if (value3 == 1){
		dir = RIGHT;
	}
	else if (value4 == 1){
		dir = DOWN;
	}
	return 1;
}
void gameMechanics()
{
	if(score == 9){
		x = true;
		gameOver = true;
	}
	int prevX = snakeX[0];
    int prevY = snakeY[0];
    int prevX2, prevY2;
    snakeX[0] = cols;
    snakeY[0] = rows;
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
            --cols;
            break;
        case RIGHT:
			++cols;
            break;
        case UP:
            rows++;
            break;
        case DOWN:
            rows--;
            break;
        default:
            break; 
	}
	if (rows > rowMax || rows < 0 || cols > colMax || cols < 0)
    {
        gameOver = true;
    }
    
    for (int i = 0; i < snakeLength; i++)
    {
        if (snakeX[i] == cols && snakeY[i] == rows){
            gameOver = true;
        }
    }
	if (rows == foodRow && cols == foodCol){
		score += 1;
		++snakeLength;
		++foodCol;
		if (foodCol > 15){
			foodCol = 5;
		}
	}
}

int main(int argc, char** argv)
{
	int gamesPlayed = 0;
	int highScore = -1;
	bool end = false;
	while (!end){
		int move;
		gameSetup();
		while (!gameOver)
		{
			drawBoard();
			move = gameInput();
			gameMechanics();
			usleep(1000);
		}
		if (gameOver)
		{
			if(x){
				score = 9;
			}
			++gamesPlayed;
			if (score > highScore){
				highScore = score;
			}
			status = oledClear();
			char sc = '0' + score;
			status = oledSetTextColumns();
			status = oledSetCursor(3,6);
			status|= oledWrite("GAME OVER!");
			status = oledSetCursor(4,5);
			status|= oledWrite("SCORE: ");
			status = oledSetCursor(4,13);
			status|= oledWriteChar(sc);
			status = oledSetCursor(5,6);
			sleep(5);
			
			char hs = '0' + highScore;
			char gp = '0' + gamesPlayed;
			status = oledClear();
			status = oledSetTextColumns();
			status = oledSetCursor(3,2);
			status|= oledWrite("HIGH SCORE: ");
			status = oledSetCursor(3,17);
			status|= oledWriteChar(hs);
			status = oledSetCursor(4,2);
			status|= oledWrite("GAMES PLAYED: ");
			status = oledSetCursor(4,13);
			status|= oledWriteChar(gp);
			status = oledSetCursor(5,5);
			status|= oledWrite("PLAY AGAIN?");
			for (int i = 3; i >= 1; --i){
				char j = '0' + i;
				status = oledSetCursor(6,6);
				status|= oledWriteChar(j);
				sleep(2);
			}
			move = gameInput();
			if (value1 == 1 || value2 == 1 || value3 == 1 || value4 == 1){
				gameOver = false;
			}
			else{
				end = true;
			}
		}
	}
	status = oledClear();
    return 0;
}
