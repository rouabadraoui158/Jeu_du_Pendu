# A simple Makefile for compiling small SDL projects

# Set the compiler
CC := gcc

# Add header files here
HDRS :=

# Add source files here
SRCS := Main.c

# Name of the executable
EXEC := Main

# Default recipe
all: $(EXEC)
 
# Recipe for building the final executable
$(EXEC): $(SRCS) $(HDRS) Makefile
	$(CC) -o $@ $(SRCS)

# Recipe to clean the workspace
clean:
	rm -f $(EXEC)

.PHONY: all clean

