/*
 * exercice.c: the mecanic to declare an exercice
 */
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <gtk-2.0/gtk/gtk.h>
#include <glib-2.0/glib.h>

#include "../UI/CLE.h"
#include "exercise.h"
#include "../logo/turtle.h"
#include "../logo/world.h"

#define PIPE_SIZE 1024

exercise_t exercise_new(const char *mission, const char *template,
		f_run_t solution, world_t w) {
	exercise_t result = malloc(sizeof(struct s_exercise));
	result->mission = mission;
	result->template = template;
	result->solution = solution;
	result->w_init = w;
	result->w_curr = world_copy(w);
	result->w_goal = world_copy(w);

	/* Populate the goal world with solution turtles */
	int it;
	turtle_t t;
	world_foreach_turtle(result->w_goal,it,t) {
		turtle_set_code(t, solution);
		turtle_run(t);
	}
	return result;
}
void exercise_free(exercise_t e) {
	world_free(e->w_init);
	world_free(e->w_curr);
	world_free(e->w_goal);
	free(e);
}
/* Mutex to detect whether the demo is already running */
static GStaticMutex demo_runner_running = G_STATIC_MUTEX_INIT;

/* Shared data structure to store all children pids when they are killed*/
static pid_t* all_pids = NULL;

/* Mutex to use whenever all child processes are terminated*/
static GStaticMutex children_killed = G_STATIC_MUTEX_INIT;

/* Mutex to detect whether the student code is already running */
static GStaticMutex student_code_running = G_STATIC_MUTEX_INIT;

/* Function launched in a separate thread to run the demo without locking the UI
 * It is in charge of starting a thread for each turtle to animate, and wait for their completion
 */
void* exercise_demo_runner(void *exo) {
	int it;
	turtle_t t;

	exercise_t e = exo;
	GThread **runners = malloc(sizeof(GThread*)*(world_get_amount_turtle(e->w_goal)));

	/* Reset the goal world */
	world_free(e->w_goal);
	e->w_goal = world_copy(e->w_init);
	world_set_step_delay(e->w_goal,50); /* FIXME: should be configurable from UI */
	world_foreach_turtle(e->w_goal,it,t)
	turtle_set_code(t, e->solution);

	/* Launch all the runners */
	world_foreach_turtle(e->w_goal,it,t)
	runners[it] = g_thread_create(turtle_run,t,1,NULL);

	/* Wait the end of all runners */
	world_foreach_turtle(e->w_goal,it,t)
	g_thread_join(runners[it]);

	/* Re-enable the demo running button */
	world_set_step_delay(e->w_goal,0);
	g_static_mutex_unlock(&demo_runner_running);
	return NULL;
}
void exercise_demo(exercise_t e) {
	int res = g_static_mutex_trylock(&demo_runner_running);
	if (!res) {
		printf("Not restarting the demo (it's already running)\n");
		return;
	}

	/* Launch the demo (in a separate thread waiting for the completion of all turtles before re-enabling the button) */
	g_thread_create(exercise_demo_runner,e,0,NULL);
}
int exercise_demo_is_running() {
	int res = g_static_mutex_trylock(&demo_runner_running);
	if (res)
		g_static_mutex_unlock(&demo_runner_running);

	printf("Demo is %srunning\n",(!res?"":"NOT "));
	return !res;
}
void exercise_demo_stop(exercise_t e) {
	/* Actually, we don't stop the demo since we *need* it to compute the goal world.
	 * Instead, we stop the animation and get it computing as fast as possible.
	 * That's not what we want to do for exercise_run_stop (or whatever you call it). Instead we want to kill the child doing it.
	 */
	world_set_step_delay(e->w_goal,0);
}

void exercise_run(exercise_t e, char *source) {
	turtle_t t;
    char tmpfile[15] = "/tmp/CLEXXXXXX";
    int  tmpfile2 = mkstemp(tmpfile);
    FILE *file   =  fdopen(tmpfile2, "w+");
    //what is to be included before the student code
    char header[512] = "#include <stdio.h>\n"
"void left(double angle) {\n"
	"printf(\"1 %d (LEFT %lf)\\n\", (int)angle, angle);\n}\n"
"void right(double angle) {\n"
	"printf(\"2 %d (RIGHT %lf)\\n\", (int)angle, angle);\n}\n"
"void forward(double steps) {\n"
	"printf(\"3 %d (FORWARD %lf)\\n\", (int)steps, steps);\n}\n"
"void backward(double steps) {\n"
	"printf(\"4 %d (BACKWARD %lf)\\n\", (int)steps, steps);\n}\n"
	"#line 1 \"";

	//this must appear after the student code to prevent warnings
	char *after ="\nvoid main() {\n\t run();\n}\n";
	
	/*
	 * concatenate the header and the name of the temp file
	 * so that it prints #line 1 CLEXXXXXX
	 */
	strcat(header, tmpfile);
	strcat(header, "\"\n");

    //Write the source code in the temp file
	fprintf(file, "%s", header);
	fprintf(file, "%s", source);
	fprintf(file, "%s", after);
	feof(file);
	fclose(file);
	
	char input[PIPE_SIZE] = "";
	char output[] = "";
	int fd4[2];
	pipe(fd4);

	if(fork() == 0)
	{// code executed by child
	close(fd4[1]);
	// redirecting stderr from child to father
	dup2(fd4[1],2);
	write(fd4[1], output, 1+strlen(output)); 
	// calling gcc
	int code = execlp("gcc", "gcc", "-x","c", tmpfile, "-o", "run", (char*)NULL);
	if(code != 0) 
        { // managing problem with gcc
			printf("Cannot generate executable file\n");
			perror("Compilation error");
		}
	}
	else { //father
		close(fd4[0]);
		read(fd4[0],input, PIPE_SIZE);
		int it;
		exercise_t exo = e;
		/* thread in which the turtles will be run */ 
		GThread **run_thread = malloc(sizeof(GThread*)*(world_get_amount_turtle(exo->w_curr)));

		/* Reset the goal world */
		world_free(exo->w_curr);
		exo->w_curr = world_copy(exo->w_init);
		world_set_step_delay(exo->w_curr,50); /* FIXME: should be configurable from UI */
		world_foreach_turtle(exo->w_curr,it,t) 
			turtle_set_code(t, (f_run_t)exercise_run_one);
			
		

		/* Launch all the runners */
		world_foreach_turtle(exo->w_curr,it,t)
			run_thread[it] = g_thread_create(turtle_run,t,1,NULL);

		/* Wait the end of all runners */
		world_foreach_turtle(exo->w_curr,it,t)
			g_thread_join(run_thread[it]);
		if(world_eq(exo->w_curr, exo->w_goal)) {
				CLE_exercise_done();
			}
		/* Re-enable the run button */
		world_set_step_delay(exo->w_curr,0);
		g_static_mutex_unlock(&student_code_running);
		
		wait(NULL);
		}
    
}

void exercise_run_one(turtle_t t) {
	int c2f[2]; //child to father file descriptor
	pipe(c2f);
	int c1[2];
	pipe(c1);
	
	
	if(fork() == 0) 
	{ //child
	close(c1[0]);
	close(c2f[1]);
	dup2(c1[1], 1);
	dup2(c2f[1], 0);
		execlp("./run", "./run", (char*) NULL);
		printf("Launch all turtles\n");
		printf("Turtle rank %d running child %p\n", turtle_get_rank(t), tmpfile); 
		printf("End of execution\n");
		exit(0);
	}
	else {//father
		close(c1[1]);
		close(c2f[0]);
		FILE *fromchild = fdopen(c1[0],"r");
		char *buff = NULL;
		size_t len = 0;
		int got;
		while ((got = getline(&buff, &len, fromchild)) != -1) 
		{
		int cmd=-1;
		double arg=-1;
		sscanf(buff, "%d %lf", &cmd,&arg);
		switch(cmd)
		{
			case 1:
				turtle_left(t, arg);
				break;
			case 2:
				turtle_right(t, arg);
				break;
			case 3: 
				turtle_forward(t, arg);
				break;
			case 4:
				turtle_backward(t, arg);
				break;
		}
		}
		wait(NULL);
		fclose(fromchild);
	}
	
}

void exercise_run_stop(exercise_t e) {
	int i;
	size_t len = sizeof(all_pids);
	for (i= 0; i< len ; i++) 
	{
		g_static_mutex_unlock(&children_killed);
		all_pids[i] = getpid();
		kill(all_pids[i], SIGTERM);
		g_static_mutex_trylock(&children_killed);
	}
}

