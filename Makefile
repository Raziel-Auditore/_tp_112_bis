CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11 -Iinclude \
	-Isrc/medicaments -Isrc/lot -Isrc/laboratory -Isrc/sales -Isrc/sele-item
BUILD_DIR := build
BIN_DIR := bin
TARGET := $(BIN_DIR)/app
TEST_TARGET := $(BIN_DIR)/test_app

SRC := $(wildcard src/*.c) \
	$(wildcard src/medicaments/_logic_/*.c) \
	$(wildcard src/lot/_logic_/*.c) \
	$(wildcard src/laboratory/_logic_/*.c) \
	$(wildcard src/sales/_logic_/*.c) \
	$(wildcard src/sele-item/_logic_/*.c)
OBJ := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRC))
MAIN_OBJ := $(BUILD_DIR)/main.o
LIB_OBJ := $(filter-out $(MAIN_OBJ),$(OBJ))

TEST_SRC := $(wildcard tests/*.c)
TEST_OBJ := $(patsubst tests/%.c,$(BUILD_DIR)/test_%.o,$(TEST_SRC))

.PHONY: all clean run test

all: $(TARGET)

$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/test_%.o: tests/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_TARGET): $(LIB_OBJ) $(TEST_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
