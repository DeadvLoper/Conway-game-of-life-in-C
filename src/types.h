#ifndef TYPES_H
#define TYPES_H


#define N 25
#define M 25


typedef enum {Alive = 1, Dead = 0} State;
typedef enum {Kill , Birth} Job;

typedef struct {
	size_t x,y;
	Job job;
} CellJob;


typedef struct {
	State state;
	size_t alive_neighbours;
} Cell;

Cell cells[N*M];

CellJob jobs[N*M];


#endif
