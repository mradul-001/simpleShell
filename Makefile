CC = gcc
SRC = main.c ./src/interactive.c ./src/batch.c ./src/custom/cd.c
TARGET = shell

all: $(TARGET)

$(TARGET): $(SRC)
	@ $(CC) $(SRC) -o $(TARGET)

clean:
	@ rm -f *.o $(TARGET)

.PHONY: all clean
