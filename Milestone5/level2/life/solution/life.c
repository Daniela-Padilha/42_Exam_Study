#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(int ac, char **av) {
  if (ac != 4)
		return 1;
  
  int width = atoi(av[1]);
  int height = atoi(av[2]);
  int iter = atoi(av[3]);
  int board[height][width];

  //init board
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      board[i][j] = 0;
  
  int x = 0;
  int y = 0;
  int pen = 0;
  char c;

  //draw board
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

  int n = 0;
  int new[height][width];

  //
  for (int it = 0; it < iter; it++)
  {
    for (int y = 0; y < height ; y++)
    {
        for (int x = 0; x < width ; x++)
        {
            n = 0;
          
        }
    }
  }

  //print result
  for (int i = 0; i < height ; i++)
	{
		for(int j = 0; j < width ; j++)
			putchar(board[i][j] ? '0' : ' ');
		putchar('\n');
  }
}
