CC:=cc
CFLAGS:= -Wextra -Wall -Werror
NAME:= cube3d
INCLUDE_DIR:=include
BIN_DIR:=bin
SRC_DIR=src
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
CFLAGS += -Ofast
LIB= -lmlx -framework OpenGL -framework AppKit
endif
ifeq ($(UNAME), Linux)
CFLAGS += -O3
LIB= -lXext -lX11 -lmlx -lm
endif

SRC:= $(wildcard $(SRC_DIR)/*.c)
OBJ:=$(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC))

.DEFAULT_GOAL := $(NAME)

vpath %.c $(SRC_DIR)

echo:
	echo $(CFLAGS)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(LIB) -I$(INCLUDE_DIR) -o $@ $(OBJ)

$(BIN_DIR)/%.o : %.c include/*.h | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ -c $<

debug : CFLAGS+=-g
debug : fclean all

clean :
	rm -rf $(BIN_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)

$(BIN_DIR) :
	mkdir -p $(BIN_DIR)

.PHONY : all clean fclean re debug
.SECONDARY:
