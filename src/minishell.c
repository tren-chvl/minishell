/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:41:16 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/03 16:04:51 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parse_command_line_from_tokens(t_token *toks, int ntok)
{
	t_cmd	*head;
	t_cmd	*cur;

	head = NULL;
	cur = NULL;
	parse_tokens(toks, ntok, &head, &cur);
	return (head);
}

void	after_run(t_mini *mini, char *line)
{
	t_cmd	*cmd;
	t_token	*token;
	int		nbtok;

	token = ft_token(line, &nbtok);
	cmd = parse_command_line_from_tokens(token, nbtok);
	if (!cmd)
	{
		free_token(token, nbtok);
		return ;
	}
	if (f_ck_redirection(cmd, mini, token, nbtok) != 0)
	{
		free_cmd(cmd);
		free_token(token, nbtok);
		return ;
	}
	replace_env(mini, cmd);
	process_all_heredocs(cmd);
	exec_cmd(cmd, mini);
	free_cmd(cmd);
	free_token(token, nbtok);
	add_history(line);
}

void	run_shell(t_mini *mini)
{
	char	*line;

	disable_echoctl();
	setup_signals();
	while (1)
	{
		line = readline("ft_suicide $ ");
		if (!line)
			break ;
		if (ctrl_d(mini, line))
		{
			free(line);
			break ;
		}
		if (*line)
			after_run(mini, line);
		free(line);
	}
}

void	getpath(t_mini *mini)
{
	int		i;

	i = 0;
	mini->path = NULL;
	while (!mini->path)
	{
		i += 10;
		mini->path = getcwd(mini->path, i);
	}
	getcwd(mini->path, 1);
}

int	main(int ac, char **av, char **envp)
{
	t_mini	*mini;

	(void)ac;
	(void)av;
	mini = malloc(sizeof(t_mini));
	mini->env = NULL;
	mini->envp = envp;
	mini->prev_exit = 0;
	getpath(mini);
	fill_env(mini, envp);
	run_shell(mini);
	free_mini(mini);
	return (0);
}
