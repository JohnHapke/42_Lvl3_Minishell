# Colors
RED = \e[31m
GRN = \e[32m
YLW = \e[33m
DEF = \e[0m

NAME = Minishell

SRC := $(wildcard src/*.c) $(wildcard src/*/*.c)

OBJ = $(SRC:.c=.o)
OBJ_DIR = obj/

FLAGS = -Wall -Wextra -Werror -lreadline
LIBFT = libft/libft.a
CC = @cc $(CFLAGS)

all: $(NAME)

speak:
	@echo $(SRC)

$(NAME): speak $(OBJ_DIR) $(OBJ) $(LIBFT)
	@echo "$(GRN)Done!$(DEF)"
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(LIBFT):
	@echo "$(YLW)Compiling Minishell...$(DEF)"
	@make -C libft

%.o: %.c
	@echo "$(YLW)Compiling object files...$(DEF)"
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	@echo "$(GRN)Removing object files...$(DEF)"
	rm -f $(OBJ)

fclean: clean
	@echo "$(GRN)Removing executable...$(DEF)"
	@rm -f $(NAME)

re: fclean $(NAME)
	@echo "$(YLW)Rebuilding executable...$(DEF)"

.PHONY: all clean fclean re speak