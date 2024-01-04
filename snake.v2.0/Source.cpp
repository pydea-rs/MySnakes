#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <windows.h>
//#include <windef.h>
#include <fstream>

#define RECORD_FILE "record.dat"
#define byte_int char
#define signed_byte_int signed char
#define makeBeepSound cout << (char)7
#define point_value 10
#define differential_key_converter 76
#define right +1
#define left -1
#define up -4
#define down +4
#define correctMovementChange1 3
#define correctMovementChange2 5
#define width 79
#define height 70

struct SnakeSegment
{
public:
	SnakeSegment * nextSegment;
	byte_int x, y;
}*firstSegment, *lastSegment;

byte_int extraPointX = -1, extraPointY = -1, pointX, pointY;
short int timeToDestroyExtraPoint = 0, extraPointValue = 15, extraPointCreatingPeriod = 5, scoredPointsTillExtraPoint = 0;
short int delay = 100, ppt = 0;
byte_int delaySteps = 5;
signed_byte_int currentMove, nextMove;

bool extraPointCreated = false;
bool pointCreated = false;


signed_byte_int abs(signed_byte_int);
void gotoxy(byte_int, byte_int);
void initiateGame();
void wait(unsigned int);
void randomizeCoordinates(byte_int &x, byte_int &y);
void moveSnake(signed_byte_int);
void checkxy(byte_int&, byte_int&);
void createExtraPoint();
void checkForScore();
void distroyExtraPoint();
void endGame();


using namespace std;

int main()
{
	system("color 70");
	/*********************disable scroll bar***********************/
	signed_byte_int absMovesSum = 0;
	initiateGame();
	while (true)
	{
		if (!pointCreated)
		{
			randomizeCoordinates(pointX, pointY);
			gotoxy(pointX, pointY);
			cout << "x";
			pointCreated = true;
		}
		moveSnake(currentMove);
		if (_kbhit())
		{
			nextMove = static_cast<signed_byte_int>(_getch());
			nextMove -= differential_key_converter;
			absMovesSum = abs(currentMove + nextMove);
			if (absMovesSum == correctMovementChange1 || absMovesSum == correctMovementChange2)
				currentMove = nextMove;
		}
	}
	return 0;
}


signed_byte_int abs(signed_byte_int x)
{
	return x >= 0? x : x * -1;
}


void gotoxy(byte_int x, byte_int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


void initiateGame()
{
	srand(time(NULL));

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
	/*
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo);
	COORD newBufferSize;
	newBufferSize.X = bufferInfo.dwSize.X - 10;
	newBufferSize.Y = bufferInfo.dwSize.Y;
	if (!SetConsoleScreenBufferSize(consoleHandle, newBufferSize))
	{
		system("pause");
	}*/
	SMALL_RECT consoleSize = { 0, 0, width, height };
	SetConsoleWindowInfo(consoleHandle, TRUE, &consoleSize);
	SetConsoleTitle(static_cast<LPCSTR>("Snake"));
	
	/*HWND hwnd;
	GetScrollBarInfo(hwnd, OBJID_VSCROLL, psbi);
	ShowScrollBar(hwnd, SB_BOTH, false);*/
	nextMove = currentMove = down;
	//EnableScrollBar
	firstSegment = new SnakeSegment;
	lastSegment = new SnakeSegment;
	lastSegment->nextSegment = firstSegment;
	firstSegment->nextSegment = nullptr;
	firstSegment->x = 40;
	firstSegment->y = 12;
	lastSegment->x = 41;
	lastSegment->y = 12;

}


void wait(unsigned int timeout)
{
	timeout += clock();
	while (clock() < timeout);
}


void randomizeCoordinates(byte_int &x, byte_int &y)
{
	x = rand() % width;
	y = rand() % height;
	if (x < 1)
		x = 2;
	if (y <= 1)
		y = 2;
}


void moveSnake(signed_byte_int direction)
{
	wait(delay);

	SnakeSegment *c = lastSegment;
	gotoxy(lastSegment->x, lastSegment->y);
	cout << " ";

	byte_int nextXForFirstSegment = firstSegment->x, nextYForFirstSegment = firstSegment->y;
	if (abs(direction) == right)
		nextXForFirstSegment += direction;
	else if (abs(direction) == down)
		nextYForFirstSegment += (direction / down);
	checkxy(nextXForFirstSegment, nextYForFirstSegment);
	while (c != firstSegment)
	{
		c->x = c->nextSegment->x;
		c->y = c->nextSegment->y;
		if (extraPointCreated && extraPointX == c->x && extraPointY == c->y)
		{
			randomizeCoordinates(extraPointX, extraPointY);
			createExtraPoint();
		}
		if (pointX == c->x && pointY == c->y)
			pointCreated = false;
		checkxy(c->x, c->y);
		gotoxy(c->x, c->y);
		if (c->x == nextXForFirstSegment && c->y == nextYForFirstSegment)
			endGame();
		cout << "O";
		c = c->nextSegment;
	}

	firstSegment->x = nextXForFirstSegment;
	firstSegment->y = nextYForFirstSegment;
	gotoxy(firstSegment->x, firstSegment->y);
	cout << "@";
	checkForScore();
	if (extraPointCreated)
	{

		gotoxy(width - 3, 1);
		printf("%.3d", timeToDestroyExtraPoint);
		timeToDestroyExtraPoint--;
		if (timeToDestroyExtraPoint == 0)
		{
			gotoxy(extraPointX, extraPointY);
			cout << " ";
			distroyExtraPoint();
		}
	}

}

void checkxy(byte_int &x, byte_int &y)
{
	if (x > width)
		x = 1;
	else if (x < 1)
		x = width;
	else if (y > height)
		y = 2;
	else if (y < 2)
		y = height;
}


void createExtraPoint()
{
	gotoxy(extraPointX, extraPointY);
	cout << "X";
	timeToDestroyExtraPoint = 150;
	extraPointCreated = true;
}


void checkForScore()
{
	if (firstSegment->x == pointX && firstSegment->y == pointY)
	{
		randomizeCoordinates(pointX, pointY);
		SnakeSegment *newSegment = new SnakeSegment;
		newSegment->nextSegment = lastSegment;
		lastSegment = newSegment;
		ppt += point_value;
		delay -= delaySteps;
		if (delaySteps > 0)
			delaySteps -= (ppt / 100);
		scoredPointsTillExtraPoint++;
		if (scoredPointsTillExtraPoint == extraPointCreatingPeriod)
		{
			randomizeCoordinates(extraPointX, extraPointY);
			createExtraPoint();
		}
		gotoxy(1, 1);
		makeBeepSound	;
		cout << "PPT : " << ppt;
		pointCreated = false;
	}
	else if (firstSegment->x == extraPointX && firstSegment->y == extraPointY && extraPointCreated == true)
	{
		distroyExtraPoint();
		ppt += extraPointValue;
		extraPointValue += 5;
		gotoxy(1, 1);
		makeBeepSound	;
		cout << "PPT : " << ppt;
	}
}


void distroyExtraPoint()
{
	extraPointCreated = false;
	int r2 = rand() % 5;
	extraPointCreatingPeriod += r2;
	scoredPointsTillExtraPoint = 0;
	gotoxy(width - 3, 1);
	cout << "   ";
}


void endGame()
{
	/*******************check fort best record ***************************/
	system("cls");
	gotoxy(1, 1);
	cout << "\nYou Lose!\nYour Record : " << ppt << endl;
	unsigned short int bestRecord = 0;
	ifstream recordFile(RECORD_FILE);
	if (!recordFile)
		cout << "\nReading last best record failed...\tSomething went wrong while openning the record file...\n";
	else
	{
		recordFile >> bestRecord;
		cout << "\nBest Record:\t" << bestRecord << endl;
	}
	recordFile.close();
	if (ppt > bestRecord)
	{
		cout << "\nCongratulations :) You scored a new record ...\n";
		ofstream recordFile(RECORD_FILE);
		if (!recordFile)
			cout << "\nSaving your new best record have been failed...\tSomething went wrong while openning the record file...\n";
		else
		{
			recordFile << ppt;
			cout << "\nRecord have been successfully saved...\n";
		}
		recordFile.close();
	}

	system("pause");
	exit(0);
}