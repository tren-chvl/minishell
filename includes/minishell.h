#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <dirent.h>
#include <libft.h>

#define T_DIRENT struct dirent

volatile sig_atomic_t g_signal = 0;

typedef struct s_files {
	struct dirent	*readdir;
	struct s_files	*next;
}	t_files;

void	ls(const char *path);

#endif
