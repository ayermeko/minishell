#ifndef MINISHELL_H
# define MINISHELL_H

# define PATH_MAX	4096
# define TRUE 1
# define FALSE 0

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

int		syntax_error(char *msg);

// free_utils.c

char	*free_spaces(char *input);
void	free_array(char **av);
int		builtin_exit(char **av, t_env **minienv);

// init_minienv.c

t_env	*minienv_node(char *name, t_env *minienv);
char	*value_only(char *key_pair);
char	*minienv_value(char *name, t_env *minienv);
void	minienv_add(char *key_pair, t_env **minienv);
t_env	*init_minienv(char **environ);

// input_handle.c

char	*skip_quotes(char *str);
int		unclosed_quotes(char *input);
char	*trim_spaces_no_free(char	*input);
int		input_error(char *input, int *exit_status, t_env *minienv);

// main.c

char	*prompt_input(t_env *minienv);
int		minishell(t_env *minienv);

// pipe.c

int		pipe_start(char *input);
char	*get_next_pipe(char *str);
int		empty_pipe(char *input);

// redirect.c

char	*get_rposition(char *str);
int		unexpected_token(char *input);
int		redirect_error(char *input);

// signal_handler.c

void	signal_handler(void);

// utils.c

void	check_av_error(char **av);


#endif