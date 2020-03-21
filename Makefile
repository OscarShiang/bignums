TARGET = test
OBJ = bign.o test.o
CC = gcc
CFLAGS = -g -std=gnu11

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(CFLAGS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

format: 
	clang-format -i *.c
	clang-format -i *.h

clean:
	$(RM) $(OBJ) $(TARGET)
