# Colors
RED = \e[31m
GRN = \e[32m
YLW = \e[33m
DEF = \e[0m

NAME = minishell

SRC_DIR = src
SHELL_DIR = $(SRC_DIR)/shell
TOK_DIR = $(SRC_DIR)/tokenization
PAR_DIR = $(SRC_DIR)/parsing
EXE_DIR = $(SRC_DIR)/execution
SIG_DIR = $(SRC_DIR)/signals
BUILT_DIR = $(SRC_DIR)/builtins
CLEAN_DIR = $(SRC_DIR)/cleanup
GNL_DIR = get_next_line

SRC := $(SRC_DIR)/main.c\
		$(SHELL_DIR)/shell_init.c\
		$(SHELL_DIR)/shell_loop.c\
		$(TOK_DIR)/token_utils.c\
		$(TOK_DIR)/tokenizer.c\
		$(PAR_DIR)/command_builder.c\
		$(PAR_DIR)/expander_utils.c\
		$(PAR_DIR)/expander.c\
		$(PAR_DIR)/extract_variables.c\
		$(PAR_DIR)/parsing_handler.c\
		$(PAR_DIR)/parsing_utils.c\
		$(PAR_DIR)/token_validator.c\
		$(EXE_DIR)/execution_error.c\
		$(EXE_DIR)/execution_handler.c\
		$(EXE_DIR)/execution.c\
		$(EXE_DIR)/get_cmd_path.c\
		$(EXE_DIR)/get_relative_path.c\
		$(EXE_DIR)/pipeline_exec.c\
		$(EXE_DIR)/process_handling.c\
		$(EXE_DIR)/redirection_handling.c\
		$(SIG_DIR)/signal_handler.c\
		$(BUILT_DIR)/builtin_handler.c\
		$(BUILT_DIR)/builtin_helpers.c\
		$(BUILT_DIR)/cd.c\
		$(BUILT_DIR)/echo.c\
		$(BUILT_DIR)/env.c\
		$(BUILT_DIR)/exit.c\
		$(BUILT_DIR)/export.c\
		$(BUILT_DIR)/pwd.c\
		$(BUILT_DIR)/unset.c\
		$(CLEAN_DIR)/cleanup_shell.c\
		$(CLEAN_DIR)/error_handler.c\
		$(GNL_DIR)/get_next_line.c\
		$(GNL_DIR)/get_next_line_utils.c\



OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g
LIBFT = libft/libft.a
CC = gcc

INCLUDES = -Iinclude -Ilibft -Iget_next_line

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(GRN)Done!$(DEF)"
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	@echo "$(YLW)Compiling Libft...$(DEF)"
	@make -C libft bonus

%.o: %.c
	@echo "$(YLW)Compiling object files...$(DEF)"
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

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