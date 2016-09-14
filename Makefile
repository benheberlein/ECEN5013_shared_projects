# This is the Makefile for the projecti

CC=

CFLAGS=

# Default to compile for default 'make'
all: compile

# Compile command 
compile:
    $(CC)

# Deletes build files and executables
clean:
    rm $(PROJECT_NAME)
    # ...

# Build and execute test
test:
    $(CC) test_data.c test_memory.c test_main.c -o $(TEST_NAME)
    ./test/$(TEST_NAME)


