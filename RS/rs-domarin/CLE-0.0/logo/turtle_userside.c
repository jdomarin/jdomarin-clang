/*
 * turtle_userside.c: functions callable from user code
 */
#include <stdio.h>

void left(double angle) {
	printf("1 %d (LEFT %lf)\n", angle, angle);
}

void right(double angle) {
	printf("2 %d (RIGHT %lf)\n", angle, angle);
}

void forward(double steps) {
	printf("3 %d (FORWARD %lf)\n", steps, steps);
}

void backward(double steps) {
	printf("4 %d (BACKWARD %lf)\n", steps, steps);
}

void main() {
	run();
}
