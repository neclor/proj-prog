TARGET = app

SRC_DIR	= src
INC_DIR	= include
BIN_DIR = bin
LIB_DIR	= lib

CC = gcc
CFLAGS = --std=c99 --pedantic -Wall -W -Wmissing-prototypes $(pkg-config --cflags gtk+-2.0) -I $(INC_DIR)
LDFLAGS = $(pkg-config --libs gtk+-2.0)

SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(СС) $(OBJS) -o $@ $(LDFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/*.h
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN_DIR) $(TARGET)

test: $(TARGET)
	./$(TARGET) -f pbm -i test_image/test.pbm -o test_image/result.pbm
	./$(TARGET) -f pgm -i test_image/test.pgm -o test_image/result.pgm
	./$(TARGET) -f ppm -i test_image/test.ppm -o test_image/result.ppm

git:
	git pull
	git add .
	git commit -m Update
	git push
