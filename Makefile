SRC = #TODO ...

OBJ = $(CFILES:.c=.o)

FLAGS = -Wall -Wextra -Werror

NAME = Minishell

LIBFT = libft.a

CC = cc

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ)

cleanlibft: clean
	@make -C libft clean

fclean: clean
	rm -f $(NAME)

fcleanlibft: fclean
	@make -C libft fclean

re: fcleanlibft $(NAME)

.PHONY: all clean fclean re cleanlibft fcleanlibft