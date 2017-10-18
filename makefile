det : main.o
	gcc -o det main.o
main.o : main.c
	gcc -c -Wall -pedantic -Werror -std=c99 main.c
clean :
	rm main.o
