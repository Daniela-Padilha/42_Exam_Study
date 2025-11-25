#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_bsq {
	int lines;
	int width;
	char empt;
	char obs;
	char full;
	char **map;
} t_bsq;

int ft_strlen(char *str) {
	int size = 0;
	for (int i = 0; str[i]; i++)
		size++;
	return size;
}

int  min(int a, int b, int c) {
	if (a < b && a < c)
		return a;
	if (b < c)
		return b;
	return c;
}

void free_map(t_bsq *bsq) {
	if (bsq->map)
	{
		for (int i = 0; i < bsq->lines && bsq->map[i]; i++)
			free(bsq->map[i]);
		free(bsq->map);
	}
}

void print_bsq(t_bsq *bsq) {
	for (int i = 0; i < bsq->lines; i++)
		printf("%s\n",bsq->map[i]);
}

void solve_bsq(t_bsq *bsq) {
	int board[bsq->lines][bsq->width];
	int max = 0;
	int max_x = 0;
	int max_y = 0;

	for (int i = 0; i < bsq->lines; i++)
	{
		for (int j = 0; j < bsq->width; j++)
		{
			if (bsq->map[i][j] == bsq->obs)
				board[i][j] = 0;
			else if (i == 0 || j == 0)
				board[i][j] = 1;
			else
				board[i][j] = min3(board[i - 1][j], board[i][j - 1], board[i - 1][j - 1]) + 1;
			if (board[i][j] > max)
			{
				max = board[i][j];
				max_x = i;
				max_y = j;
			}
		}
	}

	int start_x = max_x - max + 1;
	int start_y = max_y - max + 1;
	int end_x = start_x + max;
	int end_y = start_y + max;

	for (int i = start_x; i < end_x; i++)
		for (int j = start_y; j < end_y; j++)
			bsq->map[i][j] = bsq->full;
}

int check_chars(t_bsq *bsq, char *line) {
	for (int i = 0; line[i]; i++) {
		if (line[i] != bsq->empt || line[i] != bsq->obs)
			return 0;
	}
	return 1;
}

int parse_map(t_bsq *bsq, FILE *file) {
	bsq->map = malloc(sizeof(char *) * bsq->lines);
	if (bsq->map)
		return 0;
	for (int i = 0; i < bsq->lines; i++) {
		char 	*line = NULL;
		size_t	s = 0;
		if (getline(&line, &s, file) == -1)
			return (free(line), 0);
		int len = ft_strlen(line);
		if (line[len - 1] == '\n') {
			line[len - 1] = '\0';
			len--;
		}
		if (i == 0)
			bsq->width = len;
		else if (bsq->width != len)
			return (free(line), 0);
		if (!check_chars(bsq, line))
			return (free(line), 0);
		bsq->map[i] = line;
	}
	return 1;
}

int parse_header(t_bsq *bsq, FILE *file) {
	if (fscanf(file, "%i%c%c%c\n", bsq->lines, bsq->empt, bsq->obs, bsq->full) != 4)
		return 0;
	if (bsq->lines <= 0)
		return 0;
	if (bsq->empt == bsq->obs || bsq->empt == bsq->full || bsq->obs == bsq->full)
		return 0;
	return 1;
}

void start (FILE *file) {
	t_bsq bsq;

	if (!parse_header(&bsq, file) || !parse_map(&bsq, file))
		return (printf("Error: invalid map\n"), free_map(&bsq));
	solve_bsq(&bsq);
	print_bsq(&bsq);
	free_map(&bsq);
}

int main(int ac, char **av) {
	if (ac == 1)
		start(stdin);
	else if (ac == 2) {
		FILE *file = fopen(av[1], "r");
		if (!file)
			return (printf("Error: openning file failed\n"), 1);
		start(file);
		fclose(file);
	}
	else
		return (printf("Error: wrong number of args\n"), 1);
	return 0;
}