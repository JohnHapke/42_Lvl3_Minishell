/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:09:36 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/11 17:15:53 by iherman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

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

extern volatile sig_atomic_t	g_signal;

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
	E_NEWLINE,
	E_REDIR, 
	E_OTHER
}			t_exec_error;

typedef enum e_error_code
{
	ERROR_EXIT_FAILURE = 1,
	ERROR_USAGE = 2,
	ERROR_CMD_NOT_EXECUTABLE = 126,
	ERROR_CMD_NOT_FOUND = 127,
	ERROR_MEMORY_ALLOC
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
	t_env	 *env_list;		// Linked list of environment variables (for builtins)
	t_env	 *user_env_list;	// Linked list of user added variables
	char	 **env_array;		// Array format for execve (external commands)
	int 	exit_status;		// Last exit code ($?)
	bool	should_exit;
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
int		ft_parsing_handler(t_shell *shell, char *line);

// Expansion
void		ft_expand_variables(t_shell *shell, char **value);
int			ft_expansion_handler(t_shell *shell, t_token **token_list);
void		ft_var_extract_handler(t_shell *shell, t_token **token_list);
char		*ft_get_var_key(char *str);
bool		ft_variable_check(char *value);
char		*ft_get_unquoted_str(char *str);
char		*ft_list_getenv(char *var_key, t_env *env_list, t_env *user_env_list);
char		*ft_insert_str(char *str, char *insert, int varkey_len, int *i);
t_env		*ft_find_env_node(char *var_key, t_env *env_list, t_env *user_env_list);

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

void		ft_list_close(void *data);

// Execution
int		ft_execution_handler(t_shell *shell, t_command **command);
int		ft_input_handler(t_redir *redir);
int		ft_output_handler(t_redir *redir);
int		ft_process(t_shell *shell, t_command *command, int *pipe_fd, t_list **open_pids);
void	ft_execution(t_command *command, char *cmd_path, char **env);
void	ft_free(char **path);
int		ft_control_waitpid_status(int status);

char	*ft_get_relative_cmd_path(char *cmd);
char	*ft_get_cmd_path(char *cmd, char **env);

// Builtins
int		ft_builtin_handler(t_shell *shell, t_command *command, int *pipe_fd, t_list **open_pids);
int		ft_single_builtin(t_shell *shell, t_command **command);
int		ft_cd(t_shell *shell, char **argv);
int		ft_echo(t_shell *shell, char **argv);
int		ft_env(t_shell *shell, char **argv);
int		ft_exit(t_shell *shell, char **argv);
int		ft_export(t_shell *shell, char **argv);
int		ft_pwd(t_shell *shell, char **argv);
int		ft_unset(t_shell *shell, char **argv);
int		(*ft_is_builtin(char **args))(t_shell *shell, char **args);
int		ft_builtin_error(int code, char *cmd, char *optional, char *messsage);

char	**ft_list_to_strv(t_env *env);

// Signals
void	ft_init_signals(void);
void	ft_restore_signals(void);
void	ft_set_signal(int sig_type, void (*handler)(int));

// Cleanup
void	ft_error_handler(t_error_code code, int *exit_status);
void	ft_cleanup_shell(t_shell *shell);
int		ft_process_error(t_exec_error error);
int		ft_command_error(t_exec_error error, char *cmd);
int		ft_other_error(t_exec_error error, char *arg);
/*	tbd	*/

#endif
