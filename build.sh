#! /bin/bash

nasm -f elf64 -d ELF_TYPE ./nasm_multiply.asm
gcc -o main main.c nasm_multiply.o -lcurl