/*
 * lesson.h
 *
 *  Created on: 21 oct. 2010
 *      Author: mquinson
 */
#include <stdarg.h>
#include "exercise.h"

#ifndef LESSON_H_
#define LESSON_H_

typedef exercise_t (*exercise_constructor_t)(void);
typedef struct {
	const char *label;
	exercise_constructor_t exo_constructor;
	int rank;
} exercise_desc;

typedef struct s_lesson {
	const char *title;
	int amount;
	exercise_t e_curr;
	exercise_desc *exos;
} *lesson_t;

lesson_t lesson_new(const char* title, int amount, ...);
lesson_t lesson_from_file(char *filename);
void lesson_free(lesson_t l);
void lesson_set_exo(lesson_t l, int num);

#endif /* LESSON_H_ */
