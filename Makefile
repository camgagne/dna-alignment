CC = g++
CFLAGS = --std=c++20 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

all: EDistance.a EDistance test

EDistance: main.o EDistance.o
	$(CC) $(CFLAGS) -o EDistance main.o EDistance.o $(LIB)

test: test.o EDistance.o
	$(CC) $(CFLAGS) -o test test.o EDistance.o $(LIB)

EDistance.a: EDistance.o
	ar rcs EDistance.a EDistance.o

main.o: main.cpp EDistance.hpp
	$(CC) $(CFLAGS) -c main.cpp

EDistance.o: EDistance.cpp EDistance.hpp
	$(CC) $(CFLAGS) -c EDistance.cpp

test.o: test.cpp EDistance.hpp
	$(CC) $(CFLAGS) -c test.cpp

clean:
	rm -f EDistance test test.o main.o EDistance.o EDistance.a

lint:
	cpplint *.cpp *.hpp
