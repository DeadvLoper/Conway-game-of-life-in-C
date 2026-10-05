#include "types.h"


void draw();
void update_state(Cell*);
void insert_job(CellJob);
void create_job_for(Cell*,int,int);
void perform_jobs();
int alive_neighbours(int,int);

int is_within_bounds(Point);

