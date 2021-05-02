CC = gcc
CFLAGS = -Wall -g
EXEC = apocalypse

./bin/$(EXEC) : ./obj/mainprog.o ./obj/inoutTerm.o ./obj/inoutTrad.o ./obj/inoutHist.o ./obj/regle.o
	$(CC) $(CFLAGS) -o $@ $^

./obj/mainprog.o : ./sources/mainprog.c ./headers/materiel.h ./headers/inoutTerm.h ./headers/inoutHist.h
	$(CC) $(CFLAGS) -c $< -o $@

./obj/inoutTerm.o : ./sources/inoutTerm.c ./headers/inoutTerm.h ./headers/inoutHist.h ./headers/inoutTrad.h ./headers/materiel.h ./headers/regle.h
	$(CC) $(CFLAGS) -c $< -o $@

./obj/inoutHist.o: ./sources/inoutHist.c ./headers/inoutHist.h ./headers/inoutTrad.h ./headers/materiel.h ./headers/regle.h
	$(CC) $(CFLAGS) -c $< -o $@

./obj/inoutTrad.o : ./sources/inoutTrad.c
	$(CC) $(CFLAGS) -c $< -o $@

./obj/regle.o : ./sources/regle.c ./headers/materiel.h ./headers/inoutTerm.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm ./obj/*.o
	rm ./bin/*

dist :
	zip -r ../apocalypse.zip ./