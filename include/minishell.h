#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define _POSIX_C_SOURCE 200809L

extern int	g_signal;

typedef enum e_error_code
{
	ERROR_USAGE = 0,
	ERROR_EXIT_FAILURE = 1,
	ERROR_CMD_NOT_EXECUTABLE = 126,
	ERROR_CMD_NOT_FOUND = 127,
	ERROR_PARSING,
	ERROR_MEMORY_ALLOC,
	ERROR_OPEN,
	ERROR_CLOSE
}			t_error_code;

typedef enum e_redir_type
{
	REDIR_IN,     // < (Input redirection)
	REDIR_OUT,    // > (Output redirection)
	REDIR_APPEND, // >> (Append output redirection)
	REDIR_HEREDOC // << (Here-document)
}			t_redir_type;

typedef enum e_token_type
{
	TOKEN_WORD,     // Words (commands, arguments, etc.)
	TOKEN_PIPE,     // | (Pipe operator)
	TOKEN_REDIR_IN, // < or << (Input redirections)
	TOKEN_REDIR_OUT // > or >> (Output redirections)	
}			t_token_type;

typedef struct s_token
{
	t_token_type type;    // Token type
	char *value;          // Token value (string)
	struct s_token *next; // Next token in the list
}			t_token;

typedef struct s_redir
{
	t_redir_type type;    // Redirection type (in, out, append, heredoc)
	char *file;           // File name or delimiter for heredoc
	struct s_redir *next; // Next redirection in the list
}			t_redir;

typedef struct s_command
{
	char **args;            // Command arguments (including the command itself)
	t_redir *redirs;        // List of redirections
	struct s_command *next; // Next command (for pipes)
}			t_command;

typedef struct s_env
{
	char *key;          // Variable name (e.g., "HOME")
	char *value;        // Variable value (e.g., "/home/user")
	struct s_env *next; // Next environment variable in the list
}			t_env;

typedef struct s_shell
{
	t_env *env_list;  // Linked list of environment variables (for builtins)
	char **env_array; // Array format for execve (external commands)
	int exit_status;  // Last exit code ($?)
}			t_shell;

// init_shell
void	ft_init_shell(t_shell *shell, char **envp);

void	ft_token_handler(char *line);

#endif
