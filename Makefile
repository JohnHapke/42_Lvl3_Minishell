# Colors
RED = \e[31m
GRN = \e[32m
YLW = \e[33m
DEF = \e[0m

NAME = minishell

SRC := $(wildcard src/*.c) $(wildcard src/*/*.c)

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra  -g -O0 #-fsanitize=address#TEMP -Werror
LIBFT = libft/libft.a
CC = @cc $(CFLAGS)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(GRN)Done!$(DEF)"
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	@echo "$(YLW)Compiling Libft...$(DEF)"
	@make -C libft bonus

%.o: %.c
	@echo "$(YLW)Compiling object files...$(DEF)"
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	@echo "$(GRN)Removing object files...$(DEF)"
	@rm -f $(OBJ)

fclean: clean
	@make -C libft fclean
	@echo "$(GRN)Removing executable...$(DEF)"
	@rm -f $(NAME)

re: fclean $(NAME)
	@echo "$(YLW)Rebuilding executable...$(DEF)"

.PHONY: all clean fclean re speak