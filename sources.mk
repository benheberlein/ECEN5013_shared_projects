OUTPUT_NAME = project

# Source files
SRCS      = main.c \
            data.c \
            memory.c \
            project1.c \
						circbuf.c \
						log.c\
						profiler.c

LIBS_SRCS = data.c \
            memory.c \
						circbuf.c \
						log.c\
						profiler.c

TEST_SRCS = test_main.c \
            test_data.c \
            test_memory.c \
						test_circbuf.c
