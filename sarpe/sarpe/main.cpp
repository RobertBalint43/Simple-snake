#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
bool gameOver;
bool print;
const int width = 40;
const int height = 20;
int x, y, fruitx, fruity, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2; 
	fruitx = rand() % (width - 1);
	fruity = rand() % (height - 1);
	score = 0;
}


void Draw()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });

	for (int i = 0; i < width + 1; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1 )
				cout << "#";
			else if (i == y && j == x)
				cout << "O";
			else if (i == fruity && j == fruitx)
				cout << "F";
			else
			{
				print = false;
				for (int k = 0; k < nTail; k++)

					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
			}
			if(!print)

				cout << " ";
				
		}
		cout << endl;

	}
	for (int i = 0; i < width + 1 ; i++)
		cout << "#";

	cout << endl;

	cout << "Score: " << score << endl;

	
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'a':
				dir = LEFT;
				break;

			case 'w':
				dir = UP;
				break;

			case 's':
				dir = DOWN;
				break;
			
			case 'd':
				dir = RIGHT;
				break;

			case 'x':
				gameOver = true;
				break;
		}	

	}

}

void Logic()
{
	int prevX, prevY;
	prevX = tailX[0];
	prevY = tailY[0];
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

	if (x < 0 || x > width || y > height || y < 0)
		gameOver = true;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitx && y == fruity)
	{
		score = score + 10;
		fruitx = rand() % (width - 1);
		fruity = rand() % (height - 1);
		nTail++;

	}

}



int main()

{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(80);
		
		
	}

	if (gameOver)
		cout << endl <<  "GAME OVER!" << endl;

	return 0;
}