CC:=cc
CFLAGS:= -Wextra -Wall -g #-Werror -g
NAME:= cube3d
INCLUDE_DIR:=include
BIN_DIR:=bin
SRC_DIRS= src $(patsubst %/, %, $(sort $(dir $(wildcard src/*/))))
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
CFLAGS += -Ofast
LIB= -lmlx -framework OpenGL -framework AppKit
endif
ifeq ($(UNAME), Linux)
CFLAGS += -O3
LIB= -lXext -lX11 -lm -lbsd
endif

INCLUDES:= $(wildcard $(INCLUDE_DIR)/*.h)
SRC:= $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJ:= $(patsubst %.c, $(BIN_DIR)/%.o, $(notdir $(SRC)))

.DEFAULT_GOAL := $(NAME)

vpath %.c $(SRC_DIRS)

echo:

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $(OBJ) libmlx.a $(LIB) 

$(BIN_DIR)/%.o : %.c $(INCLUDES) | $(BIN_DIR)
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
