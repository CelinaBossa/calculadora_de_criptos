#! /bin/bash

as -o main.o calculadora_cripto.asm
gcc -shared -o main.so main.o
