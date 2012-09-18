CC = gcc
all: avl.c
	gcc -g -D_AVL_TEST avl.c
out.exe: main.o avltree.o
#	gcc main.o avltree.o -o out.exe
main.o: main.c avltree.h
#	gcc -c main.c 
avltree.o: avltree.c avltree.h
#	gcc -c avltree.c 
