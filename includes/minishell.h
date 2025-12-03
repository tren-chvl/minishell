/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:57:10 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/02 16:16:19 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int			bef;
}	t_token;

typedef struct s_tokft
{
    t_token **toks;
    int      *n;
    int      *cap;
}   t_tokft;

typedef struct s_fttokinit
{
    char    *line;
    t_token *toks;
    int     cap;
    int     n;
    int     i;
    int     space;
    t_tokft tokctx;
}   t_fttokinit;


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
int		arg_count(t_cmd *cmd);
int skip_spaces(char *line, int *i);
void    *ft_realloc(void *ptr, size_t old_count, size_t new_count, size_t elem_size);

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
void free_token(t_token *token, int nbtok);
void	free_tab(char **tab);
void	free_cmd(t_cmd *cmd);

//parsing
int		open_outfile(t_cmd *cmd);
char	*read_word(char *line, int *i);
void	para_argv(t_cmd *cmd, char *s);
void	exec_build(t_cmd *cmd, t_mini *mini);
t_token	*ft_token(char *line, int *ntok);
int		f_ck_redirection(t_cmd *cmd, t_mini *mini, t_token *toks, int ntok);
void	str_hasenv(t_mini *mini, char **str_ptr);
int		is_in_quotes(char *str, int pos);
void	process_all_heredocs(t_cmd *cmds);
void	process_heredoc(t_cmd *cmd);
int		ft_signe(char c);
int		is_builtin(char *cmd);
void	exec_cmd(t_cmd *cmd, t_mini *mini);
void	exec_no_build(t_cmd *cmd, t_mini *mini);
void	replace_env(t_mini *mini, t_cmd *cmd);
int		is_in_quotes(char *str, int pos);
void	ft_redirection(t_cmd *cmd, t_mini *mini);
char	**get_env_path(t_list *env);
char	*find_exec(t_mini *mini, char *cmd);
void	run_middle_list( t_cmd *cmd, int *prev_fd, t_mini *mini);
pid_t	exec_last_child(int prev, t_cmd *cmd, t_mini *mini);
pid_t	run_commands_list(t_cmd *cmd_list, t_mini *mini);
int		ft_isspace(char c);
t_cmd	*parse_command_line(char *line);
void    handle_redir(t_cmd *res, t_token *toks, int nbtok, int *i);
#endif
