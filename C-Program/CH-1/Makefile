# Set compiler
#========================================================================
CC = gcc

#========================================================================
# Compiler flags:
# -Wall = enable all warnings
# -g    = include debugging information
#========================================================================
CFLAGS = -Wall -g

#========================================================================
# SRCS: grab all .c files in the current directory
#========================================================================
SRCS = $(wildcard *.c)

#========================================================================
# TARGETS: make a list of executables by removing ".c" from each source file
# Example: main.c utils.c → main utils
#========================================================================
TARGETS = $(SRCS:.c=)

#========================================================================
# OBJS: make a list of object files by replacing ".c" with ".o"
# Example: main.c utils.c → main.o utils.o
#========================================================================
OBJS = $(SRCS:.c=.o)

#========================================================================
# Default rule: build all executables
# "make" with no arguments will build everything in $(TARGETS)
#========================================================================
all: $(TARGETS)

#========================================================================
# Rule to build an executable from its object file
# %:%.o  → for any file X, "X" depends on "X.o"
# $@ = target (executable name)
# $< = first dependency (the .o file)
#========================================================================
# For multiple Targets
#%: %.o
#	$(CC) $(CFLAGS) -o $@ $<

# For single Target
$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGETS) $(OBJS)

#========================================================================
# Rule to compile a .c source into a .o object file
# %.o:%.c  → for any file X.c, create X.o
# $< = source file
# -o $@ = output file (the object file)
#========================================================================
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#========================================================================
# Clean rule: delete all .o files and executables
# Run "make clean" to remove compiled files
#========================================================================
clean:
	rm -f *.o $(TARGETS)

#========================================================================
# Run rule: "make run-main" will build & run ./main
# "make run-utils" will build & run ./utils
# $< = target program (executable)
#========================================================================	
#run-%: %
#	./$<

#========================================================================
# For single file
run:$(TARGETS)
	./$(TARGETS)
