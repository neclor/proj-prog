TARGET = filtre


SRC_DIR	= src
LIB_DIR	= lib
OBJ_DIR = build


CC = gcc
CFLAGS = -I $(SRC_DIR) -I $(LIB_DIR)
CFLAGS += --std=c99 --pedantic -Wall -W -Wextra -Wmissing-prototypes
LDFLAGS = lib/pnm/libpnm.a


SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
LIBS = $(shell find $(LIB_DIR) -type f -name "*.a")


all: $(TARGET)


$(TARGET): $(OBJS)
	$(СС) $(OBJS) -o $@ $(LDFLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR) $(TARGET)




pnm_tests:
	echo $(LIBS)

pnm_librairie:
	make -C lib/pnm


doc:


git:
	git pull
	git add .
	git commit -m Update
	git push
