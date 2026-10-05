#include <stdio.h>
#include <unistd.h>

#include "defs.h"
#include "types.h"

int jobCount = -1;

int main() {

	useconds_t micro_s = 500000;

	int x = 5;
	int y = 5;

	/* Glider  */	
		cells[(y - 1)][x].state 	= Alive;
		cells[y][x + 1].state 		= Alive;
		cells[(y + 1)][x + 1].state 	= Alive;
		cells[(y + 1)][x].state 	= Alive;
		cells[(y + 1)][x - 1].state 	= Alive;
	/* End Glider  */	
		cells[0][x].state 		= Alive;
		cells[1][x].state 		= Alive;    		
		cells[2][x].state 		= Alive;	
	
	




	while(1)  {
		printf("\e[2J");
		perform_jobs();
		draw();
		usleep(micro_s);
	}
	return 0;
}



void draw() {

	for(int y = 0; y < ROWS; y++) {
		for(int x = 0; x < COLS; x++) {
			Cell *cell = (Cell*) &cells[y][x];
			int aliveNeighbours = alive_neighbours(x, y);
			cell->alive_neighbours = aliveNeighbours;
			if(cell->state == Alive) {
				printf("1");
			}
			else
				printf(" ");
			printf(" ");
			create_job_for(cell, x, y);
		} 
		putchar('\n');
	}
}
void create_job_for(Cell *cell,int x, int y) {
	if(cell->state == Alive) {
	if(cell->alive_neighbours < 2 || cell->alive_neighbours > 3) {
			CellJob job = {
				.x = x,
				.y = y,
				.job = Kill,
			};
			insert_job(job);
		}
			
	} 
	else if(cell->alive_neighbours == 3) {
			CellJob job = {
				.x = x,
				.y = y,
				.job = Birth,
			};
			insert_job(job);
	}
}
void perform_jobs() {
	while(jobCount >= 0) {
		CellJob job = jobs[jobCount--];
		if(job.job == Kill) {
			cells[job.y][job.x].state = Dead;	
		} else {
			cells[job.y][job.x].state = Alive;	
		}
	}

}
int alive_neighbours(int x, int y) {
	int count = 0;

	/*  pos = (N * y) + x */
	/*  t_ = top */
	/*  m_ = mid */
	/*  b_ = bot */


	Point t_leftDiagonal 	= {.x = x - 1,.y = y - 1};
	Point t_up 		= {.x = x,.y = y - 1};
	Point t_rightDiagonal   = {.x = x + 1,.y = y - 1};
	Point m_left 		= {.x = x - 1,.y = y};
	Point m_right 		= {.x = x + 1,.y = y};
	Point b_leftDiagonal 	= {.x = x - 1,.y = y + 1};
	Point b_down 		= {.x = x,.y = y + 1};
	Point b_rightDiagonal	= {.x = x + 1,.y = y + 1};


	Point moore_neighbours[8] = {
			t_leftDiagonal, 
			t_up, 
			t_rightDiagonal, 

			m_left, 
			m_right, 

			b_leftDiagonal,
			b_down,
		       	b_rightDiagonal,
		};


	for(int i = 0; i < 8; i++) {
		Point neighbour = moore_neighbours[i];
		if(is_within_bounds(neighbour)) {
			if(cells[neighbour.y][neighbour.x].state == Alive) 
				count++;
		}
	}


	return count;
}

void insert_job(CellJob job) {
	jobs[++jobCount] = job;
}

int is_within_bounds(Point p) {
	if(0 <= p.x && p.x <= COLS)
		if(0 <= p.y && p.y <= ROWS)
			return 1;
	return 0;
}
