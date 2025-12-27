CC      := gcc
# Note: On macOS, 'gcc' is often a symlink to 'clang'.
# Clang requires -Xpreprocessor -fopenmp to compile, but just -lomp to link.
CFLAGS  := -std=c11 -O2 -Wall -Wextra -Wpedantic \
           -Xpreprocessor -fopenmp \
           -I/opt/homebrew/opt/libomp/include
LDFLAGS := -L/opt/homebrew/opt/libomp/lib -lomp -lm

TEST_SRCS := $(wildcard tests/*.c)
TEST_OBJS := $(patsubst tests/%.c,bin/%.o,$(TEST_SRCS))
LIB_OBJ   := bin/binary_tree.o
ALL_OBJS  := $(TEST_OBJS) $(LIB_OBJ)

.PHONY: all clean pre-build

all: pre-build $(ALL_OBJS)
	$(CC) $(ALL_OBJS) -o ./bin/test $(LDFLAGS)

pre-build:
	mkdir -p ./bin

# Compile test files
bin/%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile the tree library
bin/binary_tree.o: binary_tree.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf ./bin