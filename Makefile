# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Iheaders -Wall -Wextra -g

# Source files
SRCS = mathigraphs.c src/starter.c src/help.c src/bar.c

# Object files
OBJS = $(SRCS:.c=.o)

# Output binary
TARGET = mathigraphs

# Default rule: build binary
all: $(TARGET)

# Link object files + static library into the final binary
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -L. -lmathi -o $(TARGET)

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and binary
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild everything AND run automatically
rebuild: clean all
	./$(TARGET)
