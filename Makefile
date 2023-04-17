CC := gcc
AS := as
NASM := nasm

SRC_DIR := src
BUILD_DIR := build

ASM_SRC := $(SRC_DIR)/multiply.asm
ASM_OBJ := $(BUILD_DIR)/multiply.o
NASM_SRC := $(SRC_DIR)/nasm_multiply.asm
NASM_OBJ := $(BUILD_DIR)/nasm_multiply.o
EXE := $(BUILD_DIR)/main

SRC := $(wildcard $(SRC_DIR)/*.c)

CFLAGS   := -Wall -Wextra -Wpedantic -Werror -Wconversion -std=gnu11
NASM_FLAGS := -f elf64 -d ELF_TYPE

.PHONY: all clean

all: $(ASM_OBJ) $(NASM_OBJ) $(EXE)


$(ASM_OBJ): $(ASM_SRC) | $(BUILD_DIR)
	$(AS) -o $@ $<

$(NASM_OBJ): $(NASM_SRC) | $(BUILD_DIR)
	$(NASM) $(NASM_FLAGS) $< -o $(NASM_OBJ) 

$(EXE): $(SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< $(NASM_OBJ) -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BUILD_DIR)

-include $(OBJ:.o=.d)