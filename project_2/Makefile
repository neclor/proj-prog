TARGET = app

SRC_DIR	= src
LIB_DIR	= lib
OBJ_DIR = build

CC = gcc
CFLAGS = --std=c99 --pedantic -Wall -W -Wmissing-prototypes $(pkg-config --cflags gtk+-2.0)
LDFLAGS = $(pkg-config --libs gtk+-2.0)

SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(СС) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR) $(TARGET)

git:
	git pull
	git add .
	git commit -m Update
	git push
