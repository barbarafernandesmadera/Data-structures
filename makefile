all: programaTrab

CC    := gcc
SRC   := $(wildcard src/*.c)
OBJ   := $(SRC:src/%.c=bin/%.o)
FLAGS :=  -I headers #-Wall -fsanitize=address -g3

programaTrab: $(OBJ)
	$(CC) -o programaTrab $(OBJ) $(FLAGS)

run: clean all
	./programaTrab

bin:
	mkdir -p bin

bin/%.o: src/%.c bin
	$(CC) -c -o $@ $< $(FLAGS)

clean:
	rm -rf bin/*

compile: clean all

zip:
	rm Trabalho.zip
	zip Trabalho.zip -r headers src makefile