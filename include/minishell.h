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

// init_minienv.c

t_env	*minienv_node(char *name, t_env *minienv);
char	*value_only(char *key_pair);
char	*minienv_value(char *name, t_env *minienv);
void	minienv_add(char *key_pair, t_env **minienv);
t_env	*init_minienv(char **environ);

// signal_handler.c

void	signal_handler(void);

// trim_spaces.c

char	*trim_spaces(char *input);
char	*trim_spaces_no_free(char	*input);
void	free_array(char **av);

// input_error.c

int		input_error(char *input, int *exit_status, t_env *minienv);

// builit_exit.c

void	builtin_exit(char **av, t_env **minienv);

#endif