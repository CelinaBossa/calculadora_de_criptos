#! /bin/bash

as -o main.o calculadora_cripto.asm
gcc -shared -o multiply.so main.o
gcc -c -Wall -Werror -fpic multiplication.c
