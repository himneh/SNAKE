#include "SConsole.h"


enum Direction { UP, DOWN, LEFT, RIGHT, PAUSE };
enum Menu { U, D, ENTER, BACK };
struct coordinate
{
	int x, y;
};
istream& operator >> (istream& inDev, coordinate& toado)
{
	inDev >> toado.x >> toado.y;
	return inDev;
}
ostream& operator << (ostream& outDev, const coordinate& toado)
{
	outDev << toado.x << " " << toado.y;
	return outDev;
}
struct Snake
{
	coordinate* dot = NULL;
	int length = 1;
	Direction dr = RIGHT;
};

coordinate obstacle[5] = { {46,13 }, {18, 9}, { 73,18 }, { 18,18 }, { 73,9 } };
coordinate park[20] = { {44,8}, {42,9}, {40,10}, {38,11}, {36,12},
{36,14}, {38,15}, {40,16}, {42,17}, {44,18}, {48,18}, {50,17}, {52,16}, {54,15}, {56,14},
	{56,12}, {54,11}, {52,10}, {50,9}, {48,8} };
char len[47] = "*19120481@19120529@19120563@19120583@19120595@";
typedef char str[100];
 str line[4] = { " 1->NEW GAME", " 2->LOAD GAME",  " 3->HIGHT SCORE"," 4->EXIT"  };

 void create(Snake& snake, coordinate& food, int mark);
 void createwall();
 void display(Snake snake, coordinate food, coordinate tail, char* len, int challenge);
 coordinate snakecontrol(Snake& snake);
 void processing(Snake& snake, coordinate& food, int& mark, int& challenge);
 bool gameover(Snake& snake, coordinate* obstacle, int challenge);
 void losing(Snake& snake, int challenge);
 void createobstacles(int challenge);
 void speed(int challenge);
 void createpark();
void printmenu();
void printlogo();
Menu key(int z);
int menucontrol(str line [4], int & selection);

int main()
{
	int choice = 0;
	int a = menucontrol(line, choice);
	switch (choice)
	{
	case 0:
	{
		clrscr();
		setTextColor(15);
		srand(time(NULL));
		Snake snake;
		coordinate food;
		int mark = 0, challenge = 1;


		createwall();
		create(snake, food, mark);

		while (true)
		{
			coordinate tail = snakecontrol(snake);

			display(snake, food, tail, len, challenge);

			losing(snake, challenge);
			if (gameover(snake, obstacle, challenge)) break;

			processing(snake, food, mark, challenge);

			speed(challenge);
		}

		delete[] snake.dot;
	}
	case 1:
	{
		clrscr();
		cout << "chon 2 thanh cong";
		break;
	}
	case 2:
	{
		clrscr();
		cout << "chon 3 thanh cong";
		break;
	}
	case 3:
	{
		clrscr();
		cout << "chon 4 thanh cong";
		break;
	}
	}

	return 0;

}

void create(Snake& snake, coordinate& food, int mark)
{
	snake.dot = new coordinate[snake.length];
	for (int i = 0; i < snake.length; i++)
	{
		snake.dot[i].x = 8 + snake.length - i - 1;
		snake.dot[i].y = 6;
	}
	snake.dr = RIGHT;
	food.x = 7 + rand() % (consolex - 4);
	food.y = 7 + rand() % (consoley - 4);
}
void createwall()
{
	for (int i = 5; i <= 5 + consoley; i++)
	{
		gotoXY(5, i);
		putchar(186);
		gotoXY(5 + consolex, i);
		putchar(186);
	}
	for (int i = 5; i <= 5 + consolex; i++)
	{
		gotoXY(i, 5);
		putchar(205);
		gotoXY(i, 5 + consoley);
		putchar(205);
	}
}
void display(Snake snake, coordinate food, coordinate tail, char* len, int challenge)
{
	noCursorType();
	gotoXY(food.x, food.y);
	putchar('O');
	gotoXY(11 + consolex, 8);
	cout << "     CHALLENGE " << challenge;
	for (int i = 0; i < snake.length; i++)
	{
		gotoXY(snake.dot[i].x, snake.dot[i].y);

		putchar(len[i]);
	}
	gotoXY(tail.x, tail.y);
	cout << " ";
}
coordinate snakecontrol(Snake& snake)
{
	Snake s;
	coordinate tail = snake.dot[snake.length - 1];
	for (int i = snake.length - 1; i > 0; i--)
	{
		snake.dot[i] = snake.dot[i - 1];
	}
	if (_kbhit())
	{
		int key = _getch();

		if (key == KEY_UP && snake.dr != DOWN)		snake.dr = UP;
		else if (key == KEY_DOWN && snake.dr != UP)	snake.dr = DOWN;
		else if (key == KEY_LEFT && snake.dr != RIGHT)	snake.dr = LEFT;
		else if (key == KEY_RIGHT && snake.dr != LEFT)  snake.dr = RIGHT;
		else if (key == 32)
		{
			s.dr = snake.dr;
			snake.dr = PAUSE;
		}
	}

	if (snake.dr == UP)	snake.dot[0].y--;
	else if (snake.dr == DOWN)	snake.dot[0].y++;
	else if (snake.dr == LEFT)	snake.dot[0].x--;
	else if (snake.dr == RIGHT)	snake.dot[0].x++;
	else if (snake.dr == PAUSE)
	{
		gotoXY(38, 7);
		cout << "PAUSE !!!!";
		while (true)
		{
			if (_kbhit())
			{
				int key2 = _getch();
				// SPACE
				if (key2 == 32)
				{
					snake.dr = s.dr;
					gotoXY(38, 7);
					cout << "RESUME !!!!";
					Sleep(800);
					gotoXY(38, 7);
					cout << "                       ";
					break;
				}
				else
					continue;
			}
		}
	}

	return tail;
}
void processing(Snake& snake, coordinate& food, int& mark, int& challenge)
{
	gotoXY(11 + consolex, 9);
	cout << "Mark : " << mark;
	gotoXY(11 + consolex, 10);
	cout << "Earn 9 marks to come to ";
	gotoXY(11 + consolex, 11);
	cout << "next challenge ";
	if (snake.dot[0].x == food.x && snake.dot[0].y == food.y)
	{
		snake.length++;
		coordinate* anew = (coordinate*)realloc(snake.dot, snake.length * sizeof(coordinate));
		if (anew != NULL)
		{
			if (snake.dr == UP) {
				anew[snake.length - 1].y = anew[snake.length - 2].y++;
				anew[snake.length - 1].x = anew[snake.length - 2].x;
			}
			else if (snake.dr == DOWN)
			{
				anew[snake.length - 1].y = anew[snake.length - 2].y--;
				anew[snake.length - 1].x = anew[snake.length - 2].x;
			}
			else if (snake.dr == LEFT)
			{
				anew[snake.length - 1].y = anew[snake.length - 2].y;
				anew[snake.length - 1].x = anew[snake.length - 2].x++;
			}
			else if (snake.dr == RIGHT)
			{
				anew[snake.length - 1].y = anew[snake.length - 2].y;
				anew[snake.length - 1].x = anew[snake.length - 2].x--;
			}
			snake.dot = anew;
			mark++;
		}
		if (mark == 9)
		{
			gotoXY(16, 12);
			cout << "Congratulation. A more difficult challenge is waiting for you ";
			mark = 0;
			gotoXY(11 + consolex, 9);
			cout << "Mark : " << mark;
			challenge++;
			Sleep(2000);
			gotoXY(16, 12);
			cout << "                                                              ";
			createobstacles(challenge);

		}
		food.x = 7 + rand() % (consolex - 4);
		food.y = 7 + rand() % (consoley - 4);
		if (challenge == 5)
		{
			while (food.x <= 56 && food.x >= 36) food.x = 7 + rand() % (consolex - 3);
		}
		if (mark == 8 && challenge == 4)
		{
			while (food.x <= 62 && food.x >= 30) food.x = 7 + rand() % (consolex - 3);
		}
		for (int i = 0; i < 5; i++)
		{
			if (food.x == obstacle[i].x && food.y == obstacle[i].y) food.y = 7 + rand() % (consoley - 3);
		}
		if (challenge == 5 && mark == 8)
		{
			food.x = 46;
			food.y = 13;
		}

	}

}
bool gameover(Snake& snake, coordinate* obstacle, int challenge)
{
	if (snake.dot[0].y == 5) return true;
	if (snake.dot[0].y == 5 + consoley) return true;
	if (snake.dot[0].x == 5) return true;
	if (snake.dot[0].x == 5 + consolex) return true;
	for (int i = 2; i <= snake.length; i++)
	{
		if (snake.dot[0].x == snake.dot[i].x && snake.dot[0].y == snake.dot[i].y)
			return true;
	}
	if (challenge == 1) return false;
	if (challenge >= 2)
	{
		if (snake.dot[0].x == obstacle[0].x && snake.dot[0].y == obstacle[0].y) return true;
	}
	if (challenge >= 3)
	{
		if (snake.dot[0].x == obstacle[1].x && snake.dot[0].y == obstacle[1].y) return true;
		if (snake.dot[0].x == obstacle[2].x && snake.dot[0].y == obstacle[2].y) return true;
	}
	if (challenge >= 4)
	{
		if (snake.dot[0].x == obstacle[3].x && snake.dot[0].y == obstacle[3].y) return true;
		if (snake.dot[0].x == obstacle[4].x && snake.dot[0].y == obstacle[4].y) return true;
	}
	if (challenge == 5)
	{
		for (int i = 0; i < 20; i++)
		{
			if (snake.dot[0].x == park[i].x && snake.dot[0].y == park[i].y) return true;
		}
	}
	return false;
}
void losing(Snake& snake, int challenge)
{
	if (gameover(snake, obstacle, challenge))
	{
		clrscr();

		setTextColor(11);
		DrawingText('S', 29, 2);
		DrawingText('N', 39, 2);
		DrawingText('A', 49, 2);
		DrawingText('K', 59, 2);
		DrawingText('E', 68, 2);

		gotoXY(46, 12);
		cout << "Oh no! You lost.";
		Sleep(3000);
		clrscr();
	}
}
void createobstacles(int challenge)
{
	if (challenge == 2)
	{
		gotoXY(obstacle[0].x, obstacle[0].y);
		putchar((char)220);
	}
	else if (challenge == 3)
	{
		gotoXY(obstacle[1].x, obstacle[1].y);
		putchar((char)219);
		gotoXY(obstacle[2].x, obstacle[2].y);
		putchar((char)219);
	}
	else if (challenge == 4)
	{
		gotoXY(obstacle[3].x, obstacle[3].y);
		putchar((char)219);
		gotoXY(obstacle[4].x, obstacle[4].y);
		putchar((char)219);
	}
	else createpark();

}
void createpark()
{

	for (int i = 0; i < 20; i++)
	{
		gotoXY(park[i].x, park[i].y);
		putchar((char)220);
	}
}
void speed(int challenge)
{
	
	Sleep(180 - (challenge - 1) * 30);
}
void printmenu()
{

		gotoXY(45, 10);
		setTextColor(4);
		cout << " 1->NEW GAME";
		Sleep(200);
		gotoXY(45, 10);
		setTextColor(6);
		cout << " 1->NEW GAME";

		gotoXY(45, 12);
		setTextColor(4);
		cout << " 2->RESUME";
		Sleep(200);
		gotoXY(45, 12);
		setTextColor(6);
		cout << " 2->RESUME";

		gotoXY(45, 14);
		setTextColor(4);
		cout << " 3->HIGHT SCORE";
		Sleep(200);
		gotoXY(45, 14);
		setTextColor(6);
		cout << " 3->HIGHT SCORE";

		gotoXY(45, 16);
		setTextColor(4);
		cout << " 4->EXIT";
		Sleep(200);
		gotoXY(45, 16);
		setTextColor(6);
		cout << " 4->EXIT";
	
}
void printlogo()
{
	setTextColor(11);
	DrawingText('S', 29, 2);
	DrawingText('N', 39, 2);
	DrawingText('A', 49, 2);
	DrawingText('K', 59, 2);
	DrawingText('E', 68, 2);
}
Menu key( int z)
{
	if (z == 224)
	{
		char key;
		key = _getch();
		if (key == 72) return U;
		if (key == 80) return D;
	}
	else if (z == 13) return ENTER;
}
int menucontrol(str line[4], int & selection)
{
	printlogo();
	printmenu();
	
	int* color = new int[4];
	for (int i = 0; i < 4; i++) color[i] = notselectcolor;
	color[0] = selectedcolor;
	while (true)
	{
		for (int i = 0; i < 4; i++)
		{
			setTextColor(color[i]);
			gotoXY(45, 10 + 2 * i);
			cout << line[i];
		}
		int z = _getch();
		Menu choice = key(z);
		switch (choice)
		{
			case U:
			{
				if (selection == 0) selection = 3;
				else selection --;
				break;
			}
			case D:
			{
				if (selection == 3) selection = 0;
				else selection++;
				break;
			}
			case ENTER: return selection;
		}
		for (int i = 0; i < 4; i++) color[i] = notselectcolor;
		color[selection] = selectedcolor;
		
	}
}

