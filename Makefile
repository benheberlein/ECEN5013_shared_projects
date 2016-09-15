###########################################################
# Makefile
#
# Date: 9/14/16
#
# Description:
# This is the Makefile for the project. It holds the build
# configuration across multiple platforms: Ubuntu Linux,
# Beagle Bone Black, and Freedom Freescale KL25Z.
#
# Author: Ben Heberlein
#
###########################################################

# Compilation and linking
##########################################################
CC      = gcc
LD      = ld
CFLAGS  = -Wall -Wextra -I$(INC_DIR)
LDFLAGS = -lc --entry main

# Directories and search paths
##########################################################
# Search paths
VPATH = src:test

# Include directory
INC_DIR = include

# Build directory
BUILD_DIR = build

# Binary directory
BIN_DIR = bin

# Test directory
TEST_DIR  = test

# directory commands
MKDIR_P = mkdir -p
RM_F    = rm -f

# Sources and objects
###########################################################
# Output file name
OUTPUT_NAME = project

# Source files
SRCS    = main.c \
          data.c \
          memory.c \
          project1.c

# Associate each object file with a source
OBJS := $(SRCS:.c=.o)

# Test sources
TEST_SRCS = test_main.c \
            test_data.c \
            test_memory.c 
TEST_NAME = test
TEST_OBJS := $(TEST_SRCS:.c=.o)

# Targets
###########################################################
# Default to compile project for default 'make'
all: $(BIN_DIR)/$(OUTPUT_NAME)

$(BIN_DIR)/$(OUTPUT_NAME): $(addprefix $(BUILD_DIR)/, $(OBJS))
	@$(MKDIR_P) $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.c
	@$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Deletes build files and executables
.PHONY: clean
clean:
	@$(RM_F) $(BUILD_DIR)/*
	@$(RM_F) $(BIN_DIR)/*
	@echo Successfully cleaned.

# Build and execute test
.PHONY: test
test: $(addprefix $(BUILD_DIR)/, $(TEST_OBJS))
	@$(MKDIR_P) $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^
	@echo Running unit tests...
	@echo Test results:
	@$(BIN_DIR)/$(TEST_NAME)




