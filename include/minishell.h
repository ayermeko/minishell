#ifndef MINISHELL_H
# define MINISHELL_H

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

#endif