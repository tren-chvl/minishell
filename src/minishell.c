/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:41:16 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/01 15:31:59 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


 void run_shell(t_mini *mini)
{
	char	*line;
	int		i;
	t_cmd	*cmd;

	i = 0;
	disable_echoctl();
	setup_signals();
	while (1)
	{
		line = readline("ft_suicide $ ");
		if (ctrl_d(mini, line))
			break ;
		if (*line)
		{
			cmd = parse_command_line(line);
			replace_env(mini, cmd);
			process_all_heredocs(cmd);
			exec_cmd(cmd, mini);
			free_cmd(cmd);
			add_history(line);
		}
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
	getpath(mini);
	fill_env(mini, envp);
	run_shell(mini);
	free_mini(mini);
	return (0);
}
