#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

void move_arrow_key(char chr, int *x, int *y, int x_b, int y_b);
void gotoxy(int x, int y);
void draw_Omokpan(int c, int r);
void play_game(void);
void display_stone(int matrix[][20][20]);
int game_end(int matrix[][20][20], int other, int x, int y);

int main(void)
{
	play_game();
	return 0;
}

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b)
{
	switch (key)
	{
	case 72:
		*y1 = *y1 - 1; 
		if (*y1 < 1)
			*y1 = 1;
		break;
	case 75:
		*x1 = *x1 - 2; 
		if (*x1 < 1)
			*x1 = 1;
		break;

	case 77:
		*x1 = *x1 + 2;
		if (*x1 > x_b)
			*x1 = x_b;
		break;

	case 80:
		*y1 = *y1 + 1; 
		if (*y1 > y_b)
			*y1 = y_b;
		break;
	default:
		return;
	}
}
void draw_Omokpan(int c, int r)
{
	int i, j;
	unsigned char a = 0xa6;
	unsigned char b[19];

	for (int i = 1; i < 19; i++)
	{
		b[i] = 0xa0 + i;
	}
	printf("%c%c", a, b[3]);

	for (int i = 0; i < c - 1; i++)
	{
		printf("%c%c", a, b[8]);
	}
	printf("%c%c", a, b[4]);
	printf("\n");

	for (int i = 0; i < r - 1; i++)
	{
		printf("%c%c", a, b[7]);
		for (int j = 0; j < c - 1; j++)
		{
			printf("%c%c", a, b[11]);
		}
		printf("%c%c", a, b[9]);
		printf("\n");
	}
	printf("%c%c", a, b[6]);

	for (int i = 0; i < c - 1; i++)
	{
		printf("%c%c", a, b[10]);
	}
	printf("%c%c", a, b[5]);
	printf("\n");
}
void play_game(void)
{
	int x = 1, y = 1, other = 0;
	int matrix[2][20][20] = { 0 };
	char key;
	char *stone[2] = { "○", "●" };
	do
	{
		gotoxy(1, 24);
		printf("                                                  ");
		gotoxy(1, 1);
		draw_Omokpan(18, 18);
		gotoxy(x, y);
		printf("%s", stone[other]);
		display_stone(matrix);
		gotoxy(1, 20);
		printf("방향키로 움직이고 스페이스바로 돌을 놓으시오");	
		gotoxy(1, 21);		
		key = _getch();
		if (key == 27)
		{
			exit(0);
		}		
		else if (key == 32)
		{
			matrix[other][(x + 1) / 2][y] = 1;
			other = 1 - other;
			if (game_end(matrix, 1 - other, x, y) == 1)
			{
				gotoxy(1, 24);
				printf("흑돌이 이겼습니다\n");
				break;
			}

			else if (game_end(matrix, 1 - other, x, y) == 2)
			{
				gotoxy(1, 24);
				printf("백돌이 이겼습니다\n");
				break;
			}
		}
		else if (key >= 72)
		{
			move_arrow_key(key, &x, &y, 37, 19);
		}
	} 
	while (1);
}

void display_stone(int matrix[][20][20])
{	
	char *stone[2] = { "○", "●" };	   
	for (int i = 0; i < 2; i++)
	{
		for (int x = 1; x < 20; x++)
		{
			for (int y = 1; y < 20; y++)
			{
				if (matrix[i][x][y] == 1)
				{
					gotoxy(x * 2 - 1, y);
					printf("%s", stone[i]);
				}
			}
		}			
	}
}

int game_end(int matrix[][20][20], int other, int x, int y)

{

	int count = 0;


	if (matrix[other][(x + 1) / 2][y])
	{
		count++;
	}
	while (count) 
	{
		for (int j = 1; j <= 4; j++)
		{
			if (matrix[other][((x + 1) / 2) - j][y] && (((x + 1) / 2) - j) >= 1)
			{
				count++;
			}
			else
			{
				count = 0; 
			}
		}

		if (count == 5)
		{
			return (other + 1);
		}
	}
	count++;
	while (count) 
	{
		for (int j = 1; j <= 4; j++)
		{
			if (matrix[other][((x + 1) / 2) + j][y] && (((x + 1) / 2) + j) <= 20)
			{
				count++;
			}	
			else
			{
				count = 0;
			}
		}
		if (count == 5)
		{
			return (other + 1);
		}
	}
	count++;

	while (count)
	{
		for (int j = 1; j <= 4; j++)
		{
			if (matrix[other][((x + 1) / 2)][y - j] && (y - j) >= 1)
			{
				count++;
			}
			else
			{
				count = 0;
			}
		}
		if (count == 5)
		{
			return (other + 1);
		}
	}
	count++;

	while (count) // ↓
	{
		for (int j = 1; j <= 4; j++)
		{
			if (matrix[other][((x + 1) / 2)][y + j] && (y + j) <= 20)
			{
				count++;
			}
			else
			{
				count = 0;
			}
		}
		if (count == 5)
		{
			return(other + 1);
		}
	}

	count++;

	while (count) // ↗
	{
		for (int j = 1; j <= 4; j++)
		{
			if (matrix[other][((x + 1) / 2 + j)][y - j] && (y - j) >= 1 && (((x + 1) / 2) + j) <= 20)
			{
				count++;
			}
			else
			{
				count = 0;
			}
		}
		if (count == 5)
		{
			return (other + 1);
		}
	}
	count++;

	while (count) // ↙

	{

		for (int j = 1; j <= 4; j++)
		{
			if (matrix[other][((x + 1) / 2 - j)][y + j] && (y + j) <= 20 && (((x + 1) / 2) - j) >= 1)
			{
				count++;
			}
			else
			{
				count = 0;
			}
		}

		if (count == 5)
		{
			return (other + 1);
		}
	}
	count++;

	while (count) 
	{
		for (int j = 1; j <= 4; j++)
		{
			if (matrix[other][((x + 1) / 2 - j)][y - j] && (y - j) >= 1 && (((x + 1) / 2) - j) >= 1)
			{
				count++;
			}
			else
			{
				count = 0;
			}
		}
		if (count == 5)
		{
			return (other + 1);
		}
	}
	count++;

	while (count) 
	{
		for (int j = 1; j <= 4; j++)
		{
			if (matrix[other][((x + 1) / 2 + j)][y + j] && (y + j) <= 20 && (((x + 1) / 2) + j) <= 20)
			{
				count++;
			}
			else
			{
				count = 0;
			}
		}
		if (count == 5)
		{
			return (other + 1);
		}		
	}
	return 0; 
}