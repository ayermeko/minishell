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

// buildins

int			cd(char **av, t_env *minienv);
int			echo(char **av);
int			env(t_env *minienv);
int			builtin_exit(char **av, t_env **minienv);
int			pwd(void);

// builtin_exec.c

int			execute_builtin(char **av, t_env **minienv);
int			is_builtin(char *cmd);

// error_msg.c

int			syntax_error(char *token);
void		print_perror_msg(char *command, char *perror_msg);
void		print_error_msg(char *command, char *msg);
void		exit_with_error(char *command, char *msg, int error);

// expand_input.c

char		*find_var_position(char *input);
char		*find_exit_status_position(char *input);
void		expand_exit_status(char **input, int exit_status);
void		expand_input(char **input, t_env *minienv, int exit_status);

// fd_handler.c

void		close_all_fds(void);

// free_utils.c

char		*free_spaces(char *input);
void		free_array(char **av);

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
char 		*value_only(char *key_pair);
char		*minienv_value(char *name, t_env *minienv);
void		minienv_add(char *key_pair, t_env **minienv);
t_env		*init_minienv(char **environ);

// parser.c

char		*skip_quotes(char *str);
int			unclosed_quotes(char *input);
char		*trim_spaces_no_free(char	*input);
int			input_error(char *input, int *exit_status, t_env *minienv);
void		check_av_error(char **av);

// pipe.c

int			has_pipe(char *str);
int			pipe_start(char *input);
int			empty_pipe(char *input);

// redirect_io.c

void		redirect_fd(int fd_to_redirect, int fd_location);
void		save_original_fd(int original_fds[2], int fd_index);
int			redirect_input(char *input);
int			redirect_output(char *command);
int			handle_io(char *command, int original_fds[2], int fd_type);

// redirect.c

void		restore_original_fds(int original_fds[2]);
char 		*get_spos(char *str, const char *chars_to_find);
int			unexpected_token(char *input);
int			redirect_error(char *input);
int			handle_redirects(char *input, int original_fds[2]);

// scanner.c

char		**split_av(char *input);

// signal_handler.c

int			handle_signal_interrupt(int status, int is_last_child);
int			wait_for_child(int child_pid, int is_last_child);
void		define_heredoc_signals(int child_pid);
void		signal_handler(void);

// utils.c

int			fits_in_long_long(char *str);
int 		is_command(char *str1, char *str2);
void		delete_char(char *str, int len);
long long	ft_atoll(const char *str);
void		redirect_heredoc(char *command);

#endif
