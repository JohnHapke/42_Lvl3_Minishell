/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhapke <jhapke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:09:36 by jhapke            #+#    #+#             */
/*   Updated: 2025/06/29 17:15:48 by jhapke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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
# include <stdbool.h>

# define _POSIX_C_SOURCE 200809L

extern int	g_signal;

/* Data strucutres */

typedef enum e_exec_error
{
	E_FORK,
	E_PIPE,
	E_DUP,
	E_DUP2,
	E_CMD,
	E_PERMISSION,
	E_OPEN,
	E_ACCESS,
	E_MEM,
	E_OTHER
}			t_exec_error;

typedef enum e_error_code
{
	ERROR_EXIT_FAILURE = 1,
	ERROR_USAGE = 2,
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

typedef enum	e_token_type
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
	struct s_token	*next; // Next token in the list
	struct s_token	*prev;
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
	t_env *env_list;		// Linked list of environment variables (for builtins)
	t_env *user_env_list;	// Linked list of user added variables
	char **env_array;		// Array format for execve (external commands)
	int exit_status;		// Last exit code ($?)
}			t_shell;

//*  functions   *//

//* Shell
void		ft_env_add_back(t_env **lst, t_env *new_node);
t_env		*ft_env_new_node(char *key, char *value);
void		ft_shell_init(t_shell *shell, char **envp);
void		ft_shell_loop(t_shell *shell);

//* Tokenization
void		ft_token_handler(t_shell *shell, t_token **token_list, char *line);

t_token		*ft_token_new_node(char *value, t_token_type type);
void		ft_token_add_back(t_token **token_list, t_token *new_node);
void		ft_token_lstclear(t_token **lst);

//* Parsing
int			ft_token_validator(t_token *token_list);
void		ft_parsing_handler(t_shell *shell, char *line);

// Expansion
void		ft_expand_variables(t_shell *shell, char **value);
void		ft_expansion_handler(t_shell *shell, t_token **token_list);
void		ft_var_extract_handler(t_shell *shell, t_token **token_list);
char		*ft_get_var_key(char *str);
bool		ft_variable_check(char *value);
char		*ft_get_unquoted_str(char *str);
char		*ft_list_getenv(char *var_key, t_env *env_list, t_env *user_env_list);
char		*ft_insert_str(char *str, char *insert, int varkey_len, int *i);

// Commands
t_redir_type	ft_get_redir_type(char	*value);
void			ft_command_handler(t_shell *shell, t_token *token_list, t_command **command);
int				ft_count_arguments(t_token *token_list);

// Command list
void		ft_command_add_back(t_command **command, t_command *new_node);
void		ft_command_lstclear(t_command **lst);


// Redir list
t_redir		*ft_new_node_redir(char	*file, t_redir_type type);
void		ft_redir_add_back(t_redir **list, t_redir *new_node);

// Execution
void	ft_execution_handler(t_shell *shell, t_command *command);
void	ft_input_handler(t_shell *shell, t_redir *redir);
void	ft_output_handler(t_shell *shell, t_redir *redir);
void	ft_process(t_shell *shell, int pipe_fd[2], char **args);
void	ft_execution(t_shell *shell, char **args, char **env);
void	ft_free(char **path);


// Builtins
/*	tbd	*/

// Signals
/*	tbd	*/

// Cleanup
void	ft_error_handler(t_error_code code, int *exit_status);
void	ft_cleanup_shell(t_shell *shell);
int		ft_process_error(t_exec_error error, int *exit);
int		ft_command_error(t_exec_error error, char *cmd, int *exit);
int		ft_str_error(t_exec_error error, char *arg, int *exit);
/*	tbd	*/


#endif
