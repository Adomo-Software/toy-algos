
#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

enum Block {
	Wall = '#',
	Path = ' ',
	Been = 'B',
	Dead = 'X',
	Start = 'S',
	End = 'E',
};

enum Direction {
	Up = 0,
	Right,
	Down,
	Left,
};

typedef struct {
	int x;
	int y;
} Vec;

Vec vec_set(int x, int y) {
    return (Vec) {
        .x = x,
        .y = y
    };
}
void vec_print(Vec vec) {
	printf("%d %d\n", vec.x, vec.y);
}

void vec_go(Vec *vec, enum Direction dir) {
	dir = dir % 4;
    switch(dir) {
        case Left:
            vec->x -= 1;
            break;
        case Up:
            vec->y -= 1;
            break;
        case Right:
            vec->x += 1;
            break;
        case Down:
            vec->y += 1;
            break;
    }
}



typedef struct {
	int w;
	int h;
	char** data;
} Maze;

void maze_print(Maze maze) {
	for (int y=0; y<maze.h; y++) {
		for (int x=0; x<maze.w; x++) {
			char c = maze.data[y][x];
			printf("%c", c);
		}
		printf("\n");
	}
}
void maze_print_jeff(Maze maze, Vec loc_jeff, enum Direction dir) {
	for (int y=0; y<maze.h; y++) {
		for (int x=0; x<maze.w; x++) {
			if (loc_jeff.x == x && loc_jeff.y == y) {

				dir = dir % 4;
				switch(dir) {
					case Left:
						printf(">");
						break;
					case Up:
						printf("^");
						break;
					case Right:
						printf("<");
						break;
					case Down:
						printf("v");
						break;
				}
				continue;
			}
			char c = maze.data[y][x];
			printf("%c", c);
		}
		printf("\n");
	}
}
enum Block vec_go_block
	(Vec *vec, enum Direction dir, Maze maze) {
	vec_go(vec, dir);
	return (enum Block)maze.data[vec->x][vec->y];
}



bool all_directions_tested(int tested_directions) {
    return tested_directions == 0b1111;
}

int mark_direction_tested(int tested_directions, enum Direction dir) {
    return tested_directions | (1 << dir);
}

#include <unistd.h>
#include <assert.h>

void maze_find_path(Maze maze, Vec loc, enum Direction dir, int tested_directions) {
	Vec prev_loc = loc;
	vec_go(&loc, dir);
	enum Block b = (enum Block)maze.data[loc.y][loc.x];
	printf("\033[H\033[J");
	maze_print_jeff(maze, prev_loc, dir % 4);

	usleep(50000);
	tested_directions = mark_direction_tested(tested_directions, dir);

	switch(b) {
		case End:
			printf("\033[H\033[J");
			maze_print_jeff(maze, loc, dir % 4);
			printf("'%c'\n", b);
			vec_print(loc);
			exit(0);
			return;
		case Path:
			maze.data[prev_loc.y][prev_loc.x] = Been;
			maze_find_path(maze, loc, 0, tested_directions);
			/*return;*/
		case Wall:
		case Start:
		case Been:
			if (all_directions_tested(tested_directions)) {
				maze.data[prev_loc.y][prev_loc.x] = Dead; // Jeff is dead
				return;
			}
			maze_find_path(maze, prev_loc, (dir + 1) % 4, tested_directions);
	}
}

int main (int argc, char *argv[]) {

	ssize_t read;
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	stream = fopen("themaze", "r");
	if (stream == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	Maze maze;
	fscanf(stream, "%d %d", &maze.w, &maze.h);
	maze.data = malloc(maze.h * sizeof(char *));
    for (int i = 0; i < maze.h; i++) {
        maze.data[i] = malloc(maze.w * sizeof(char));
    }


	printf("%d %d\n", maze.w, maze.h);

	fgetc(stream);

	Vec end_loc;
	Vec jeff_loc;
	{
		int x = 0;
		int y = 0;
		char c;
		while (y < maze.h && (c = getc(stream)) != EOF) {
			if (c == '\n') {
				if (x != maze.w) {
					fprintf(stderr, "Error: line length is less then maze width.\n");
					exit(EXIT_FAILURE);
				}
				y++;
				x = 0;
			} else {
				if (x >= maze.w) {
					fprintf(stderr, "Error: line length is more maze width.\n");
					exit(EXIT_FAILURE);
				}
				maze.data[y][x] = c;
				switch(c) {
					case Start:
						jeff_loc = vec_set(x, y);
						break;
					case End:
						end_loc = vec_set(x, y);
						break;
				}
				x++;
			}
		}
	}
	maze_print(maze);

	Vec vec = {.x = 0, .y = 0};
	vec_print(vec);
	maze_find_path(maze, jeff_loc, 0, 0);
	return 0;
}
