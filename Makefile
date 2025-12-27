CC      := gcc
CFLAGS  := -std=c11 -O2 -Wall -Wextra -Wpedantic \
           -Xpreprocessor -fopenmp \
           -I/opt/homebrew/opt/libomp/include
LDFLAGS := -lm -L/opt/homebrew/opt/libomp/lib -lomp

# 1. Separate the source files by location
TEST_SRCS := $(wildcard tests/*.c)

# 2. Define Object files
# Transform tests/test.c -> bin/test.o
TEST_OBJS := $(patsubst tests/%.c,bin/%.o,$(TEST_SRCS))
# Manually add the library object
LIB_OBJ   := bin/binary_tree.o

# Combine them all
ALL_OBJS  := $(TEST_OBJS) $(LIB_OBJ)

all: pre-build $(ALL_OBJS)
	$(CC) $(ALL_OBJS) -o ./bin/test

pre-build:
	mkdir -p ./bin

# Rule 1: Compile files found in tests/
bin/%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule 2: Compile the binary_tree.c (found in root)
bin/binary_tree.o: binary_tree.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf ./bin