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

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <ctype.h>
# include <termios.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <libft.h>

extern volatile sig_atomic_t	g_signo;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum s_toktype
{
	TOK_WORD,
	TOK_PIPE,
	TOK_GT,
	TOK_GTGT,
	TOK_LT,
	TOK_LTLT
}	t_toktype;

typedef struct s_token
{
	t_toktype	type;
	char		*val;
}	t_token;

typedef struct s_mini
{
	int		prev_exit;
	char	*path;
	char	**envp;
	int		last;
	t_list	*env;
}	t_mini;

typedef struct s_cmd
{
	int				buildtin;
	char			*path;
	char			**argv;
	char			*outfile;
	char			*intfile;
	char			*here_doc;
	char			*delimiter;
	int				append;
	int				here_fd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_envpath
{
	char	*path;
	char	**paths;
	int		i;
	char	*tmp_str;
}	t_envpath;

void	free_mini(t_mini *mini);

//commands functions
void	mini_export(t_mini *mini, t_cmd *cmd);
void	mini_echo(t_cmd *cmd);
void	mini_pwd(t_mini *mini);
void	ft_suicide(t_mini *mini, int code, t_cmd *cmd);
void	mini_cd(t_mini *mini, t_cmd *path);
void	mini_env(t_mini *mini);
void	mini_unset(t_mini *mini, t_cmd *cmd);

//commands utils
void	swap_last(t_mini *mini);
t_env	*get_lowest(t_list *list);
t_env	*get_highest(t_list *list);
void	print_env_alpha(t_mini *mini);

//debug functions
void	print_env(t_mini *mini);

//env functions
void	fill_env(t_mini *mini, char **envp);
t_env	*envnew(char *name, char *value);
t_env	*find_env(t_list *list, char *name);

//command ctrl
void	ctrl_c(int signe);
void	ctrl_back_slash(int signe);
int		ctrl_d(t_mini *mini, char *line);
void	setup_signals(void);
void	run_shell(t_mini *mini);
void	disable_echoctl(void);

//free functions
void	free_env(void *content);

//parsing
void	process_all_heredocs(t_cmd *cmds);
void	process_heredoc(t_cmd *cmd);
int		ft_signe(char c);
int		is_builtin(char *cmd);
void	exec_cmd(t_cmd *cmd, t_mini *mini);
t_cmd	*parse_command(char **para, t_mini *mini);
void	exec_no_build(t_cmd *cmd, t_mini *mini);
void	replace_env(t_mini *mini, t_cmd *cmd);
int		is_in_quotes(char *str, int pos);
void	ft_redirection(t_cmd *cmd, t_mini *mini);
char	**get_env_path(t_list *env);
char	*find_exec(t_mini *mini, char *cmd);
void	run_middle_list( t_cmd *cmd, int *prev_fd, t_mini *mini);
pid_t	exec_last_child(int prev, t_cmd *cmd, t_mini *mini);
pid_t	run_commands_list(t_cmd *cmd_list, t_mini *mini);
void	free_tab(char **tab);
void	free_cmd(t_cmd *cmd);
int		ft_isspace(char c);
t_cmd	*parse_command_line(char *line);
int		open_outfile(t_cmd *cmd);
#endif
