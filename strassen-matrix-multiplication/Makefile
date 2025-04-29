# Set default platform to Linux (HPC)
platform ?= linux

# Platform-specific flags
ifeq ($(platform), mac)
    CC = clang++
    CFLAGS = -O2 -Xpreprocessor -fopenmp -I/opt/homebrew/include -std=c++11
    LDFLAGS = -L/opt/homebrew/lib -lomp  # OpenMP on macOS
else  # Default to Linux (HPC)
    CC = g++
    CFLAGS = -O2 -fopenmp -std=c++11
    LDFLAGS = -lgomp  # OpenMP on Linux using libgomp
endif

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/strassen_matrix_multiplication

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Default target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
