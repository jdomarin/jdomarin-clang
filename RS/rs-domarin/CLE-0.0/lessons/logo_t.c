/* logo_t.c: a simple exercise asking to draw a T*/

#include "../core/exercise.h"
#include "../logo/world.h"
#include <stdio.h>

void exo_t_solution(turtle_t this) {
	int i;
	for (i=0;i<100;i++) {
		turtle_forward(this, 1);
		turtle_backward(this, 0.5);
		turtle_left(this, 90);
		turtle_forward(this, 100);
	}
}



exercise_t logo_t_create(void) {
	world_t w = world_new(500,500);
	world_turtle_add(w,turtle_new(400,300,90.));
	exercise_t res = exercise_new("Dans cet exercice vous devez tracer un T avec une tortue",
	"void run() { \n //Please type your code here }",exo_t_solution, w);

	return res;
}

