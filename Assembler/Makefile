TARGET = hasm
CC = gcc

BUILD_DIR := ./build
SRC_DIR := ./src

SRC := $(shell find $(SRC_DIR) -name '*.c' -or -name '*.s')
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) -c $< -o $@

.PHONY: clean
clean:
	rm $(BUILD_DIR)/*.o

