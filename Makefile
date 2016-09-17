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

# Compile time flags with defaults
##########################################################
# Optionsa are HOST, BBB or FRDM
PLATFORM := HOST

# File upload address
HOST_ADDR := root@192.168.7.2: # Options are any valid host (with directory)

# Compiler executables
##########################################################
ifeq ($(PLATFORM), HOST)
 CC := gcc
else ifeq ($(PLATFORM), BBB)
 ifeq ($(UNAME_N), beaglebone)
  CC := gcc
 else
  CC := arm-linux-gnueabi-gcc
 endif
else ifeq ($(PLATFORM), FRDM)
 CC := arm-none-eabi-gcc
else
$(error PLATFORM value must be HOST, BBB, or FRDM. Platform is $(PLATFORM))
endif

LD      = ld
CFLAGS  = -Wall -Wextra -I$(INC_DIR) -std=c99
LDFLAGS = -lc --entry main
AR      = ar
XFER    = scp

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

# Directory commands
MKDIR_P = mkdir -p
RM_F    = rm -f
MV_F    = mv -f
UNAME_N = uname -n

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

# Preprocessed files
PRES := $(SRCS:.c=.i)

# Assembly files
ASSEMS := $(SRCS:.c=.s)

# Library filee
LIBS_SRCS = data.c \
            memory.c
LIBS_OBJS = $(LIB_SRCS:.c=.o)
LIB_NAME = libproject1.a

# Test sources
TEST_SRCS = test_main.c \
            test_data.c \
            test_memory.c \
            $(LIBS_SRCS)
TEST_NAME = test
TEST_OBJS := $(TEST_SRCS:.c=.o)

# Dependency file generation
DFLAGS = -M

# Targets
###########################################################
# Default to compile project for default 'make'
all: build

# Compile all objects to executable
$(BIN_DIR)/$(OUTPUT_NAME): $(addprefix $(BUILD_DIR)/, $(OBJS))
	@$(MKDIR_P) $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# remaps executable to the bin folder
.PHONY: $(OUTPUT_NAME)
$(OUTPUT_NAME): $(BIN_DIR)/$(OUTPUT_NAME)
	@echo Output will be in bin folder

# Compile individual objects from source files with dependency file
$(BUILD_DIR)/%.o: %.c
	@$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DFLAGS) -o $(BUILD_DIR)/$*.d $<
	$(CC) $(CFLAGS) -c $< -o $@

# Remaps an individual object file to the correct folder
.PHONY: %.o
%.o: $(BUILD_DIR)/%.o
	@echo Output will be in build folder

# Preprocess individual source files
$(BUILD_DIR)/%.i: %.c
	@$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(CFLAGS) -E $< -o $@

# Remaps an individual preprocessed output to the correct folder
.PHONY: %.i
%.i: $(BUILD_DIR)/%.i
	@echo Output will be in build folder

# Assemble individual source files
$(BUILD_DIR)/%.s: %.c
	@$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(CFLAGS) -S $< -o $@

# Remaps an individual assembly file to the correct folder
.PHONY: %.s
%.s: $(BUILD_DIR)/%.s
	@echo Output will be in build folder

# Build all files and link
.PHONY: build
build: $(BIN_DIR)/$(OUTPUT_NAME)

# Preprocess all files
.PHONY: preprocess
preprocess: $(addprefix $(BUILD_DIR)/, $(PRES))

# Generate assembly output of all files
.PHONY: asm-file
asm-file: $(addprefix $(BUILD_DIR)/, $(ASSEMS))

# Compile all files but do not link
.PHONY: compile-all
compile-all: $(addprefix $(BUILD_DIR)/, $(OBJS))

# Upload to Beagle Bone Black via SCP
.PHONY: upload
upload: $(BIN_DIR)/$(OUTPUT_NAME)
	@echo Uploading project to BBB with SCP
	$(XFER) $(BIN_DIR)/$(OUTPUT_NAME) $(HOST_ADDR)

# Build library from library sources
.PHONY: build_lib
build-lib: $(BUILD_DIR)/$(LIB_NAME)

$(BUILD_DIR)/$(LIB_NAME): $(addprefix $(BUILD_DIR)/, $(LIB_OBJS))
	$(AR) rcs $@ $^

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
