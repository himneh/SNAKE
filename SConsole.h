#pragma once
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;

#define BLACK_COLOR			0
#define DARK_BLUE_COLOR		1
#define DARK_GREEN_COLOR	2
#define DARK_CYAN_COLOR		3
#define DARK_RED_COLOR		4
#define DARK_PINK_COLOR		5
#define DARK_YELLOW_COLOR	6
#define DARK_WHITE_COLOR	7
#define GREY_COLOR			8
#define BLUE_COLOR			9
#define GREEN_COLOR			10
#define CYAN_COLOR			11
#define RED_COLOR			12
#define PINK_COLOR			13
#define YELLOW_COLOR		14
#define WHITE_COLOR			15

#define KEY_UP		72
#define KEY_DOWN	80
#define KEY_LEFT	75
#define KEY_RIGHT	77
#define KEY_NONE	-1
#define KEY_ENTER   13
#define KEY_SPACE   32


#define consolex 80
#define consoley 18

#define selectedcolor 4
#define notselectcolor 6
int inputKey();

void clrscr();

void DrawingText(char Text, int x, int y);

void gotoXY (int x, int y);

int whereX();

int whereY();

void noCursorType();

void setTextColor (int color);

