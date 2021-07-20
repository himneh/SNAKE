#include "SConsole.h"
using namespace std;


// Xóa màn hình
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}
//drawing logo
void DrawingText(char Text, int x, int y)
{
	if (Text == 65 || Text == 97)
	{
		gotoXY(x, y);     cout << "   00  ";     Sleep(40);
		gotoXY(x, y + 1); cout << " 00  00";     Sleep(40);
		gotoXY(x, y + 2); cout << " 00  00";     Sleep(40);
		gotoXY(x, y + 3); cout << " 000000";     Sleep(40);
		gotoXY(x, y + 4); cout << " 00  00";     Sleep(40);
	}

	else if (Text == 69 || Text == 101)
	{
		gotoXY(x, y);     cout << " 000000";     Sleep(40);
		gotoXY(x, y + 1); cout << " 00    ";     Sleep(40);
		gotoXY(x, y + 2); cout << " 000000";     Sleep(40);
		gotoXY(x, y + 3); cout << " 00    ";     Sleep(40);
		gotoXY(x, y + 4); cout << " 000000";     Sleep(40);
	}

	else if (Text == 75 || Text == 107)
	{
		gotoXY(x, y);     cout << "00    00";   Sleep(40);
		gotoXY(x, y + 1); cout << "00   00 ";   Sleep(40);
		gotoXY(x, y + 2); cout << "00 0 0  ";   Sleep(40);
		gotoXY(x, y + 3); cout << "00  00  ";   Sleep(40);
		gotoXY(x, y + 4); cout << "00    00";   Sleep(40);
	}

	else if (Text == 78 || Text == 110)
	{
		gotoXY(x, y);     cout << "00     00";  Sleep(40);
		gotoXY(x, y + 1); cout << "00 0   00";  Sleep(40);
		gotoXY(x, y + 2); cout << "00  0  00";  Sleep(40);
		gotoXY(x, y + 3); cout << "00   0 00";  Sleep(40);
		gotoXY(x, y + 4); cout << "00     00";  Sleep(40);
	}

	else if (Text == 83 || Text == 115)
	{
		gotoXY(x, y);     cout << " 000000";     Sleep(40);
		gotoXY(x, y + 1); cout << " 00    ";     Sleep(40);
		gotoXY(x, y + 2); cout << " 000000";     Sleep(40);
		gotoXY(x, y + 3); cout << "     00.";     Sleep(40);
		gotoXY(x, y + 4); cout << " 000000";     Sleep(40);
	}

}

// Di chuyển con trỏ console đến vị trí có tọa độ (x, y)
void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Lấy tọa độ x hiện tại của con trỏ console
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}

// Lấy tọa độ y hiện tại của con trỏ console
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

// Xóa con trỏ nháy
void noCursorType()
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = FALSE;
	info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

// Đổi màu chữ
// Tham số: Mã màu
void setTextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}