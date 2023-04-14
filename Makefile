CC := gcc
AS := as

SRC_DIR := src
BUILD_DIR := build

ASM_SRC := $(SRC_DIR)/*.asm
ASM_OBJ := $(BUILD_DIR)/multiply.o
EXE := $(BUILD_DIR)/main

SRC := $(wildcard $(SRC_DIR)/*.c)

CFLAGS   := -Wall -Wextra -Wpedantic -Werror -Wconversion -std=gnu11

.PHONY: all clean

all: $(ASM_OBJ) $(EXE)


$(ASM_OBJ): $(ASM_SRC) | $(BUILD_DIR)
	$(AS) -o $@ $<

$(EXE): $(SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $< $(ASM_OBJ) -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BUILD_DIR)

-include $(OBJ:.o=.d)