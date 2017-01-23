build: main.cpp c4.cpp c4.h
	g++ -Wall -o game c4.cpp main.cpp
build2: main.cpp c4.cpp c4.h
	g++ -Wall -o game -D SHOW_WIN c4.cpp main.cpp
play: build
	./game
clean: 
	-rm ./game
