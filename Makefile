all: networking_setup.o networking.o battleship.o
	gcc -o battleship networking_setup.o networking.o battleship.o

run_1: all
	./battleship 1

run_2: all
	./battleship 2

run_2_local: all
	./battleship 2 127.0.0.1

clean:
	rm -rf battleship

networking_setup.o: networking_setup.c networking.h
	gcc -c networking_setup.c

networking.o: networking.c battleship.h
	gcc -c networking.c

battleship.o: battleship.c battleship.h
	gcc -c battleship.c

compile_debug: networking_setup.c networking.c battleship.c battleship.h
	gcc -g -o battleship_debug networking_setup.c networking.c battleship.c

run_valgrind_1: compile_debug
	valgrind --leak-check=yes ./battleship_debug 1

run_valgrind_2: compile_debug
	valgrind --leak-check=yes ./battleship_debug 2 149.89.151.100

run_valgrind_2_local: compile_debug
	valgrind --leak-check=yes ./battleship_debug 2 127.0.0.1

run_gdb_1: compile_debug
	gdb battleship_debug 1

run_gdb_2: compile_debug
	gdb battleship_debug 2 149.89.151.100

run_gdb_2_local: compile_debug
	gdb battleship_debug 2 127.0.0.1
