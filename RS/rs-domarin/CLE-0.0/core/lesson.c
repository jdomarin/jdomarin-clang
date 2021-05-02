/* lesson.c: lesson handling functions */

#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>

#include "../UI/CLE.h"
#include "lesson.h"
#include "../lessons/logo.h"

void *lesson = NULL;
void *handle = NULL;

lesson_t lesson_new(const char *title, int amount, ...) {
	lesson_t res = malloc(sizeof(struct s_lesson));
	res->title = title;
	res->amount= amount;
	res->exos = malloc(sizeof(exercise_desc)*amount);
    va_list ap;
    int it;
    va_start(ap,amount);
    for (it=0;it<amount;it++) {
    	res->exos[it].label = va_arg(ap,char*);
    	res->exos[it].exo_constructor = va_arg(ap, exercise_constructor_t);
    	res->exos[it].rank = it;
    }
    va_end(ap);
    res->e_curr = res->exos[0].exo_constructor();
    return res;
}

lesson_t lesson_from_file(char *filename) {
	lesson_t res = NULL;
	char *erreur = NULL;
	int (*lesson_main)();
	lesson = dlopen(filename, RTLD_NOW);
	if(!lesson) {
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
	lesson_main = dlsym(handle, "lesson_main");
	erreur = dlerror();
	if(erreur != NULL) {
		perror(erreur);
		exit(1);
	}
	(*lesson_main)();
	free(filename);
	return res;
}

void lesson_free(lesson_t l) {
	if (!l)
		return;
	if(handle != NULL)
		dlclose(handle);
	if(lesson != NULL)
		dlclose(lesson);
	
	free(l->exos);
	free(handle);
	free(lesson);
	free(l);
}

void lesson_set_exo(lesson_t l, int num) {
	if (num>=l->amount) {
		printf("No exercise number %d in lesson %s\n",num,l->title);
		return;
	}
	if (l->e_curr)
		exercise_free(l->e_curr);
	l->e_curr = l->exos[num].exo_constructor();
	CLE_exercise_has_changed();
}
