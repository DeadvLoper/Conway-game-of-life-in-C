#include <stdio.h>
#include <unistd.h>

#include "defs.h"
#include "types.h"

int jobCount = -1;

int main() {

	int x = M / 2;
	int y = N / 2;

	/* Glider  */	
		cells[(N * (y - 1)) + x].state = Alive;
		cells[(N * (y)) + x + 1].state = Alive;
		cells[(N * (y + 1)) + x + 1].state = Alive;
		cells[(N * (y + 1)) + x ].state = Alive;
		cells[(N * (y + 1)) + x - 1].state = Alive;
	/* End Glider  */	

	while(1)  {
		printf("\e[2J");
		perform_jobs();
		draw();
		sleep(1);
	}
	return 0;
}



void draw() {
	for(int y = 0; y < N; y++) {
		for(int x = 0; x < M; x++) {
			Cell *cell = (Cell*) &cells[(N * y) + x];
			int aliveNeighbours = alive_neighbours(x, y);
			cell->alive_neighbours = aliveNeighbours;
			putchar('|');
			if(cell->state == Alive) {
				putchar('*');
			}
			else
				putchar(' ');
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
			cells[(N * job.y) + job.x].state = Dead;	
		} else {
			cells[(N * job.y) + job.x].state = Alive;	
		}
	}
}
int alive_neighbours(int x, int y) {
	int count = 0;

	/*  pos = (N * y) + x */
	/*  t_ = top */
	/*  m_ = mid */
	/*  b_ = bot */

	int t_leftDiagonal 	=  (N * (y - 1)) + (x - 1);
	int t_up 	   	=  (N * (y - 1)) + (x - 0);
	int t_rightDiagonal 	=  (N * (y - 1)) + (x + 1);

	int m_left 	  	=  (N * (y - 0)) + (x - 1);
	int m_right		=  (N * (y - 0)) + (x + 1);

	int b_leftDiagonal 	=  (N * (y + 1)) + (x - 1);
	int b_down		=  (N * (y + 1)) + (x - 0);
	int b_rightDiagonal 	=  (N * (y + 1)) + (x + 1);

	int moore_neighbours[8] = 
		{
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
		int neighbour_pos = moore_neighbours[i];
		if(0 <= neighbour_pos && neighbour_pos <= (N*M)){
			Cell cell = cells[neighbour_pos];
			if(cell.state == Alive)
				count++;
		
		}
	}


	return count;
}

void insert_job(CellJob job) {
	jobs[++jobCount] = job;
}


