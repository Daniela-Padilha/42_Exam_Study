#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(int ac, char **av) {
	//get args
	if (ac != 4)
		return 1;
	int width = atoi(av[1]);
	int height = atoi(av[2]);
	int iter = atoi(av[3]);

	//init board
	int board[height][width];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			board[i][j] = 0;

	//draw starting board
	int x = 0;
	int y = 0;
	int pen = 0;
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
		else if (c == 'x')
			pen = !pen;
		if (pen)
			board[y][x] = 1;
	}

	//run iterations
	int n = 0;
	int new[height][width];

	for (int it = 0; it < iter; it++)
	{
		for (int y = 0; y < height ; y++)
		{
			for (int x = 0; x < width ; x++)
			{
				n = 0;
				//count neighbors
				for (int yy = -1; yy <= 1 ; yy++)
					for (int xx = -1; xx <= 1 ; xx++)
						if ((xx || yy) && x + xx >= 0 && y + yy >= 0 
						&& x + xx < width && y + yy < height)
							n += board[y + yy][x + xx];
				//apply rules for dead or living
				if (board[y][x] && (n == 2 || n == 3))
					new[y][x] = 1;
				else if (!(board[y][x]) &&  n == 3)
					new[y][x] = 1;
				else
					new[y][x] = 0;
			}
		}
		//copy the new board into main board
		for (int i = 0; i < height ; i++)
			for(int j = 0; j < width ; j++)
				board[i][j] = new[i][j];
	}

	//print result
	for (int i = 0; i < height ; i++)
	{
		for(int j = 0; j < width ; j++)
			putchar(board[i][j] ? 'O' : ' ');
		putchar('\n');
	}
}
