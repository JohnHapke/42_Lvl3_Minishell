/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iherman- <iherman-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:09:36 by jhapke            #+#    #+#             */
/*   Updated: 2025/07/15 15:19:42 by iherman-         ###   ########.fr       */
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

// < (Input redirection)
// > (Output redirection)
// >> (Append output redirection)
// << (Here-document)
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}			t_redir_type;

// Words (commands, arguments, etc.)
// | (Pipe operator)
// < or << (Input redirections)
// > or >> (Output redirections)
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT
}			t_token_type;

// Token type
// Token value (string)
// Next token in the list
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// Redirection type (in, out, append, heredoc)
// File name or delimiter for heredoc
// Next redirection in the list
typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

// Command arguments (including the command itself)
// List of redirections
// Next command (for pipes)
typedef struct s_command
{
	char				**args;
	t_redir				*redirs;
	struct s_command	*next;
}			t_command;

// Variable name (e.g., "HOME")
// Variable value (e.g., "/home/user")
// Next environment variable in the list
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}			t_env;

// Linked list of environment variables (for builtins)
// Linked list of user added variables
// Array format for execve (external commands)
// Last exit code ($?)
// Bool to set for ft_exit
typedef struct s_shell
{
	t_env	*env_list;		
	t_env	*user_env_list;	
	char	**env_array;		
	int		exit_status;		
	bool	should_exit;
}			t_shell;

//*  functions   *//

//* Shell
void			ft_env_add_back(t_env **lst, t_env *new_node);
t_env			*ft_env_new_node(char *key, char *value);
void			ft_shell_init(t_shell *shell, char **envp);
void			ft_shell_loop(t_shell *shell);

//* Tokenization
void			ft_token_handler(t_shell *shell, t_token **token_list,
					char *line);

t_token			*ft_token_new_node(char *value, t_token_type type);
void			ft_token_add_back(t_token **token_list, t_token *new_node);
void			ft_token_lstclear(t_token **lst);

//* Parsing
int				ft_token_validator(t_token *token_list);
int				ft_parsing_handler(t_shell *shell, char *line);

// Expansion
int				ft_expansion_handler(t_shell *shell, t_token **token_list);
void			ft_var_extract_handler(t_shell *shell, t_token **token_list);
char			*ft_get_var_key(char *str);
bool			ft_variable_check(char *value);
char			*ft_get_unquoted_str(char *str);
char			*ft_list_getenv(char *var_key, t_env *env_list,
					t_env *user_env_list);
char			*ft_insert_str(char *str, char *insert, int varkey_len, int *i);
t_env			*ft_find_env_node(char *var_key, t_env *env_list,
					t_env *user_env_list);

// Commands
t_redir_type	ft_get_redir_type(char *value);
void			ft_command_handler(t_shell *shell, t_token *token_list,
					t_command **command);
int				ft_count_arguments(t_token *token_list);

// Command list
void			ft_command_add_back(t_command **command, t_command *new_node);
void			ft_command_lstclear(t_command **lst);

// Redir list
t_redir			*ft_new_node_redir(char	*file, t_redir_type type);
void			ft_redir_add_back(t_redir **list, t_redir *new_node);

void			ft_list_close(void *data);

// Execution
int				ft_execution_handler(t_shell *shell, t_command **command);
int				ft_begin_pipeline(t_shell *shell, t_command **command,
					t_list **open_pids, int *stdio_fd);
int				ft_redirect_handler(t_redir *redir);
int				ft_process(t_shell *shell, t_command *command, int *pipe_fd,
					t_list **open_pids);
int				ft_process_setup(t_shell *shell, t_command *cmd,
					pid_t **pid, char **cmd_path);
void			ft_execution(t_command *command, char *cmd_path, char **env);
void			ft_free(char **path);
int				ft_control_waitpid_status(int status);

char			*ft_get_relative_cmd_path(char *cmd);
char			*ft_get_cmd_path(char *cmd, char **env);

void			ft_close_pipe(int *pipe);

// Builtins
int				ft_builtin_handler(t_shell *shell, t_command *command,
					int *pipe_fd, t_list **open_pids);
int				ft_single_builtin(t_shell *shell, t_command **command);
int				ft_cd(t_shell *shell, char **argv);
int				ft_echo(t_shell *shell, char **argv);
int				ft_env(t_shell *shell, char **argv);
int				ft_exit(t_shell *shell, char **argv);
int				ft_export(t_shell *shell, char **argv);
int				ft_pwd(t_shell *shell, char **argv);
int				ft_unset(t_shell *shell, char **argv);
int				(*ft_is_builtin(char **args))(t_shell *shell, char **args);
int				ft_builtin_error(int code, char *cmd, char *optional,
					char *messsage);

void			ft_extract_node(t_env **list, t_env *remove);
char			**ft_list_to_strv(t_env *env);

// Signals
void			ft_init_signals(void);
void			ft_restore_signals(void);
void			ft_set_signal(int sig_type, void (*handler)(int));

// Cleanup
void			ft_error_handler(t_error_code code, int *exit_status);
void			ft_cleanup_shell(t_shell *shell);
int				ft_process_error(t_exec_error error);
int				ft_command_error(t_exec_error error, char *cmd);
int				ft_other_error(t_exec_error error, char *arg);
/*	tbd	*/

#endif
