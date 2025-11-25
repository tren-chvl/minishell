#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 200109L
# endif

# ifndef _XOPEN_SOURCE
#  define _XOPEN_SOURCE 500
# endif

# ifndef ECHOCTL
#  define ECHOCTL 0001000
# endif

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <dirent.h>
#include "libft.h"

#define T_DIRENT struct dirent

extern volatile sig_atomic_t g_signo;

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;

typedef struct s_mini
{
	char	*path;
	t_list	*env;
}	t_mini;

void	free_mini(t_mini *mini);

//commands functions
void	mini_export(t_mini *mini, char *name, char *value);
void	mini_echo(char *str, int n);
void	mini_pwd(t_mini *mini);
void	ft_suicide(t_mini *mini, int code);
void	mini_ls(t_mini *mini, const char *path);
void	mini_cd(t_mini *mini, char *path);
void	mini_env(t_mini *mini);
void	mini_unset(t_mini *mini, char *name);

//debug functions
void	print_env(t_mini *mini);

//env functions
void	fill_env(t_mini *mini, char **envp);
t_env	*envnew(char *name, char *value);
t_env	*find_env(t_list *list, char *name);

//command ctrl
void	ctrl_c(int signe);
void	ctrl_back_slash(int signe);
int 	ctrl_d(t_mini *mini,char *line);
void	setup_signals(void);
void	run_shell(t_mini *mini);
void	disable_echoctl(void);

//free functions
void	free_env(void *content);

#endif
