CC:=cc
CFLAGS:= -Wextra -Wall -Werror -O3
LIB= -lXext -lX11 -lmlx -lm
NAME:= cube3d
INCLUDE_DIR:=include
BIN_DIR:=bin

SRC_DIR=src

SRC:= $(wildcard $(SRC_DIR)/*.c)
OBJ:=$(patsubst %.c, $(BINDIR)/%.o, $(SRC))

.DEFAULT_GOAL := $(NAME)

vpath %.c $(SRC_DIR)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(LIB) -I$(INCLUDE_DIR) -o $@ $(OBJ)

$(BINDIR)/%.o : %.c include/*.h | $(BINDIR)
	$(CC) $(CFLAGS) $(LIB) -I$(INCLUDE_DIR) -o $@ -c $<

debug : CFLAGS+=-g
debug : fclean all

clean :
	rm -rf $(BINDIR)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)

$(BINDIR) :
	mkdir -p $(BINDIR)

.PHONY : all clean fclean re debug
.SECONDARY:
