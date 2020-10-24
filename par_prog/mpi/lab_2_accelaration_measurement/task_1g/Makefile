CC=gcc
MPICC=mpicc
CFLAGS=-lm

all: Simple Parallel

Simple: simple.c
	$(CC) -o simple simple.c $(CFLAGS)

Parallel: parallel.c
	$(MPICC)  -o parallel parallel.c $(CFLAGS)
