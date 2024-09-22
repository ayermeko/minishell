#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAILED 0
# define PATH_MAX	4096
# define LLONG_MAX 9223372036854775807
# define NO_REDIRECT -1

//errors

# define INTERRUPT 128
# define CMD_NOT_FOUND 127
# define PERMISSION_DENIED 126
# define NOT_EXECUTABLE 126
# define OUT_OF_RANGE 255
# define BUILTIN_MISUSE 2
# define FORK_ERROR -1
# define CMD_NOT_FOUND_MSG	"command not found"
# define NOT_EXECUTABLE_MSG "Is a directory"

//executes

# define IN 0
# define OUT 1

# include <stdio.h> // perror
# include <readline/readline.h> // readline
# include <readline/history.h> // history
# include <stdlib.h> // getenv
# include <unistd.h> // environ, getpwd
# include <sys/wait.h> // waitpid
# include <sys/stat.h> // stat
# include <signal.h> // sigaction
# include <fcntl.h> // open flags

# include "../extra_libs/Libft/libft.h"

typedef struct s_env
{
	char			*key_pair;
	struct s_env	*next;
}	t_env;

// error_msg.c

int			syntax_error(char *token);
void		print_perror_msg(char *command, char *perror_msg);
void		print_error_msg(char *command, char *msg);
void		exit_with_error(char *command, char *msg, int error);

// expand_input.c

void	expand_variables(char **input, t_env *minienv);
void	expand_input(char **input, t_env *minienv, int exit_status);

// fd_handler.c

void	close_extra_fds(void);
void	close_all_fds(void);

// free_utils.c

char		*free_spaces(char *input);
void		free_array(char **av);
int			builtin_exit(char **av, t_env **minienv);

// heredoc_exec.c

void		insert_string(char **input, char *var_value, char *rest_str);
char		*var_position(char *s);
void		expand_heredoc(char **input, int exit_status, t_env *minienv);
void		read_heredoc(int *exit_status, t_env *minienv, char *delimiter);

// heredoc_handler.c

int			delimiter_len(char *s);
char		*get_delimiter(char *delim_pos);
char		*get_heredoc_pos(char *str);
int			exec_heredoc(char *delimiter, int *exit_status, t_env *minienv, char *input);
int			heredoc_handler(char *input, int *exit_status, t_env *minienv);

// init_minienv.c

t_env		*minienv_node(char *name, t_env *minienv);
char		*value_only(char *key_pair);
char		*minienv_value(char *name, t_env *minienv);
void		minienv_add(char *key_pair, t_env **minienv);
t_env		*init_minienv(char **environ);

// input_handle.c

char		*skip_quotes(char *str);
int			unclosed_quotes(char *input);
char		*trim_spaces_no_free(char	*input);
int			input_error(char *input, int *exit_status, t_env *minienv);

// pipe.c

int			has_pipe(char *str);
int			pipe_start(char *input);
char		*get_next_pipe(char *str);
int			empty_pipe(char *input);

// redirect.c

char		*get_rposition(char *str);
int			unexpected_token(char *input);
int			redirect_error(char *input);

// signal_handler.c

int			handle_signal_interrupt(int status, int is_last_child);
int			wait_for_child(int child_pid, int is_last_child);
void		define_heredoc_signals(int child_pid);
void		signal_handler(void);

// utils.c

void		delete_char(char *str, int len);
void		check_av_error(char **av);
long long	ft_atoll(const char *str);
int			one_command(char *input, t_env **minienv);

#endif
