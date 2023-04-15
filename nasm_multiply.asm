; Multiply two 64-bit floating-point numbers (a and b) and store the result in result
; Inputs: xmm0 = a, xmm1 = b
; Outputs: xmm0 = result

section .text
    global multiply

multiply:
    mulsd xmm0, xmm1  ; Multiply a by b, result in xmm0
    ret               ; Return

; nasm -f elf64 -d ELF_TYPE ./nasm_mult.asm
; gcc -o main ./main.c ./nasm_mult.o
;