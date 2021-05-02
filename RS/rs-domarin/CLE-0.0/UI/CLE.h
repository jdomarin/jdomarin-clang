/*
 * CLE.h: public functions of the graphical interface
 */

#ifndef CLE_H_
#define CLE_H_

#include <gtk-2.0/gtk/gtk.h>
#include "../core/lesson.h"

typedef struct CLE_data CLE_data_t;
CLE_data_t *global_data;

/* Asks the interface to change the lesson currently displayed by the renders */
void CLE_set_lesson(lesson_t l);
/* Asks the interface to change the exercise currently displayed by the renders */
void CLE_exercise_has_changed();

/* Retrieve the source code entered by the student into the source editor */
char *CLE_get_sourcecode(void);

/* Add text to the console area (the text is free()d after use, think about strdup()ing it) */
void CLE_log_append(char*text);
/* Clear the console area */
void CLE_log_clear();
/* Displays final window */
void CLE_exercise_done();

/* The following shouldn't be accessed from outside of UI/ code */
/* Convenience macros for obtaining objects from UI file */
#define CH_GET_OBJECT( builder, name, type) \
    type( gtk_builder_get_object( builder, #name ) )
#define CH_GET_WIDGET( builder, name, data ) \
    data->name = CH_GET_OBJECT( builder, name, GTK_WIDGET)

/* Main data structure definition */
struct CLE_data
{
	/* Where to find all the widgets */
    GtkBuilder *builder;

    /* Widgets */
    GtkWidget *main_window;       /* Main application window */
    GtkWidget *drawing_world;     /* Drawing area where we draw the current world */
    GtkWidget *drawing_objective; /* Drawing area where we draw the goal world */
    GtkWidget *mission_view;      /* Text area where the mission is displayed */
    GtkWidget *source_view;       /* Source editor */
    GtkWidget *log_view;          /* Text area serving as a console */

    GtkNotebook *world_views;

    /* the current lesson */
    lesson_t lesson;
};


#endif /* CLE_H_ */
