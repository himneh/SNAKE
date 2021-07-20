#include "xlSnake.h"
#include "SConsole.h"

char len[47] = "#19120481@19120529@19120563@19120583@19120595@";
int main()
{
	//Menu
	setTextColor(11);
	DrawingText('S', 29, 2);
	DrawingText('N', 39, 2);
	DrawingText('A', 49, 2);
	DrawingText('K', 59, 2);
	DrawingText('E', 68, 2);

	setTextColor(6);
	gotoxy(45, 10); cout << " 1->NEW GAME";
	gotoxy(45, 12); cout << " 2->RESUME";
	gotoxy(45, 14); cout << " 3->HIGHT SCORE";
	gotoxy(45, 16); cout << " 4->EXIT";
	cout << "\n";
	
	int kt = 1, choice = 1;
	printmenu(kt);
	do
	{
		if (_kbhit())
		{
			int key = _getch();

			if (key == KEY_ENTER) choice = 0;

			if (choice == 1) 
				if (kt == 4)
				{
					kt = 1;
					printmenu(kt);
				}
				else
				{
					kt = kt + 1;
					printmenu(kt);
				}
		}
	} while (choice != 0);

	switch (kt)
	{
		case 1:
		{
			clrscr();
			char p;

			srand(time(NULL));
			Snake snake;
			coordinate food;
			int mark = 0, n = 0;


			createwall();
			create(snake, food);
			createobstacles();
			int color = 1 + rand() % (15 + 1 - 1);
			while (true)
			{
				coordinate tail = snakecontrol(snake);

				display(snake, food, tail, len, color);

				losing(snake);
				if (gameover(snake)) break;

				processing(snake, food, mark);

				Sleep(200);
			}

			delete[] snake.dot;
			break;
		}
		case 2:
		{
			clrscr();
			cout << "chon 2 thanh cong";
			break;
		}
		case 3:
		{
			clrscr();
			cout << "chon 3 thanh cong";
			break;
		}
		case 4:
		{
			clrscr();
			cout << "chon 4 thanh cong";
			break;
		}
	}


	
}

