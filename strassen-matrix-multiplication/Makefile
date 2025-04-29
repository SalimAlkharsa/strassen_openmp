# Default compiler and flags (Linux)
CC = g++
CFLAGS = -O2 -fopenmp -std=c++11
LDFLAGS =

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/strassen_matrix_multiplication

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

all: $(TARGET)

# Mac override
mac: CC = clang++
mac: CFLAGS = -O2 -Xpreprocessor -fopenmp -I/opt/homebrew/include -std=c++11
mac: LDFLAGS = -L/opt/homebrew/lib -lomp
mac: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean mac
