#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void print_board(int w, int h, int board[h][w])
{
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (board[y][x] == 1)
				printf("[0] ");
			else
				printf("[ ] ");
		}
		printf("\n");
	}
}

int life (char **av, int print)
{
	int width = atoi(av[1]);
	int height = atoi(av[2]);
	int iter = atoi(av[3]);
	int board[height][width];
	
	for (int i = 0; i < height ; i++)
		for(int j = 0; j < width ; j++)
			board[i][j] = 0;

	int x = 0, y = 0, pen = 0;
	char c;
	while (read(0, &c, 1))
	{
		if (c == 'w' && y > 0)
			y--;
		else if (c == 's' && y < height - 1)
			y++;
		else if (c == 'a' && x > 0)
			x--;
		else if (c == 'd' && x < width - 1)
			x++;
		else if (c == 'x' && pen)
			pen = 0;
		else if (c == 'x' && !pen)
			pen = 1;
		if (pen)
			board[y][x] = 1;
	}

	if (print)
	{
		printf("\nInitial board:\n");
		print_board(height, width, board);
	}

	int n = 0;
	int new[height][width];

	for (int it = 0; it < iter ; it++)
	{
		for (int y = 0; y < height ; y++)
		{
			for (int x = 0; x < width ; x++)
			{
				n = 0;
				for (int yy = -1; yy <= 1 ; yy++)
					for (int xx = -1; xx <= 1 ; xx++)
						if ((xx || yy) && x + xx >= 0 && y + yy >= 0 
						&& x + xx < width && y + yy < height)
							n += board[y + yy][x + xx];
				if (board[y][x] && (n == 2 || n == 3))
					new[y][x] = 1;
				else if (!(board[y][x]) &&  n == 3)
					new[y][x] = 1;
				else
					new[y][x] = 0;
			}
		}
		for (int i = 0; i < height ; i++)
			for(int j = 0; j < width ; j++)
				board[i][j] = new[i][j];
		if (print)
		{
			printf("\nIteration %d:\n", it + 1);
			print_board(height, width, board);
		}
	}
    printf("\nFinal result:\n");
    print_board(height, width, board);
	return 0;
}

int main (int ac, char** av)
{
	int print = 0;

	if (ac < 4 || ac > 5)
		return (printf("Expected: ./life width height iterations (print)\n"), 1);
	if (ac == 5)
	{
		if (av[4][0] != '0' && av[4][0] != '1')
			return (printf("Print option must be 1 or 0\n"), 1);
		print = av[4][0] - '0';
	}
	life(av, print);	
	return 0;
}