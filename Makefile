SRC_DIR := .
OBJ_DIR := obj
BIN_DIR := bin

EXE := ./bnet
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -Wall -Wextra -g 
LDFLAGS  := -Llib
LDLIBS   := -lm

.PHONY: all clean

build: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

run:
	./bnet

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR) bnet

-include $(OBJ:.o=.d)