# Colors
RED = \e[31m
GRN = \e[32m
YLW = \e[33m
DEF = \e[0m

NAME = Minishell

SRC = #TODO ...

OBJ = $(CFILES:.c=.o)
OBJ_DIR = obj/

FLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
CC = @cc $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	@echo "$(GRN)Done!$(DEF)"
	$(CC) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(LIBFT):
	@echo "$(YLW)Compiling libft...$(DEF)"
	@make -C libft

%.o: %.c
	@echo "$(YLW)Compiling object files...$(DEF)"
	$(CC) -c -o $@ $<

clean:
	@echo "$(GRN)Removing object files...$(DEF)"
	rm -f $(OBJ)

fclean: clean
	@echo "$(GRN)Removing executable...$(DEF)"
	@rm -f $(NAME)

re: fcleanlibft $(NAME)
	@echo "$(YLW)Rebuilding executable...$(DEF)"

.PHONY: all clean fclean re cleanlibft fcleanlibft