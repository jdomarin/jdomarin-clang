DEPENDENCIES=gtksourceview-2.0 libglade-2.0

CFLAGS=-g `pkg-config --cflags $(DEPENDENCIES)` -Werror -Wall -I.
LDFLAGS=`pkg-config --libs $(DEPENDENCIES)` -export-dynamic

PLUGINS=logo.so recursion.so

all: CLE $(PLUGINS)

CORE=CLE.o callbacks.o exercise.o lesson.o
LOGO=turtle.o world.o
EXOS=logo_threesquare.o logo_circle.o logo_star.o logo_t.o logo.o

EXO_HEADERS=logo/turtle.h logo/world.h lessons/logo.h

CLE: $(CORE) $(LOGO) $(EXOS)
	gcc $^ -o CLE $(LDFLAGS)
	
CLE.o: UI/CLE.c UI/CLE.h	
	$(CC) $(CFLAGS) -c $< -o $@
callbacks.o: UI/callbacks.c UI/CLE.h
	$(CC) $(CFLAGS) -c $< -o $@


turtle.o: logo/turtle.c logo/turtle.h
	$(CC) $(CFLAGS) -c $< -o $@
world.o: logo/world.c logo/world.h logo/turtle.h
	$(CC) $(CFLAGS) -c $< -o $@



exercise.o: core/exercise.c core/exercise.h
	$(CC) $(CFLAGS) -c $< -o $@
lesson.o: core/lesson.c core/lesson.h core/exercise.h
	$(CC) $(CFLAGS) -c $< -o $@

# The embeeded lesson
#####################

logo_threesquare.o: lessons/logo_threesquare.c $(EXO_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
logo_circle.o: lessons/logo_circle.c $(EXO_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
logo_star.o: lessons/logo_star.c $(EXO_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
logo_t.o: lessons/logo_t.c $(EXO_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
logo.o: lessons/logo.c $(EXO_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# A first lesson plugin
#######################
logo.so: lessons/logo.c $(EXO_HEADERS) \
         lessons/logo_threesquare.c lessons/logo_circle.c lessons/logo_star.c lessons/logo_t.c
	gcc -shared -fPIC -o $@ $^ -I.
	 
recursion.so: lessons/recursion.c $(EXO_HEADERS) \
              lessons/rec_spiral.c lessons/rec_tree.c 
	gcc -shared -fPIC -o $@ $^ -I.


clean: 
	rm -f *.o CLE $(PLUGINS)
	
