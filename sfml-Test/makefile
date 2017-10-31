snake : main.o game.o wunsz.o
	g++ -o snake main.o game.o wunsz.o -lsfml-graphics -lsfml-window -lsfml-system
main.o : main.cpp
	g++ -c -std=c++11  main.cpp
game.o : game.cpp
	g++ -c -std=c++11  game.cpp
wunsz.o : wunsz.cpp
	g++ -c -std=c++11 wunsz.cpp
clean :
	-rm main.o
	-rm game.o
