myExec: main.o person.o mystat.o
	gcc -o myExec main.o person.o mystat.o
person.o: person.h person.c mystat.h
	gcc -c person.c
mystat.o: mystat.h mystat.c
	gcc -c mystat.c
main.o: person.h main.c
	gcc -c main.c
clean:
	rm -f *.o
