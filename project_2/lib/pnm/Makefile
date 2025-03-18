TARGET = libpnm.a

SRC_DIR	= .
OBJ_DIR = build

CC = gcc
AR = ar
CFLAGS = --std=c99 --pedantic -Wall -W -Wextra -Wmissing-prototypes -I $(SRC_DIR)

SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
