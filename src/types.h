#ifndef TYPES_H
#define TYPES_H


#define ROWS 20 	/*  Rows */
#define COLS 50	/*  Columns */


typedef enum {Alive = 1, Dead = 0} State;
typedef enum {Kill , Birth} Job;
typedef struct { size_t x,y;} Point;

typedef struct {
	size_t x,y;
	Job job;
} CellJob;


typedef struct {
	State state;
	size_t alive_neighbours;
} Cell;

Cell cells[ROWS][COLS];

CellJob jobs[ROWS*COLS];


#endif
