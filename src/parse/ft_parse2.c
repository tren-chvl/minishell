/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:12:12 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/01 16:54:25 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	exec_build(t_cmd *cmd, t_mini *mini)
{
	if (!cmd)
		return ;
	if (!ft_strcmp(cmd->argv[0], "cd"))
		mini_cd(mini,cmd);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		mini_export(mini, cmd);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		mini_unset(mini, cmd);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		ft_suicide(mini, 0, cmd);
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		mini_echo(cmd);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		mini_pwd(mini);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		mini_env(mini);
}

void exec_cmd(t_cmd *cmd, t_mini *mini)
{
	if (cmd->next)
		run_commands_list(cmd, mini);
	else
	{
		if (!cmd->argv || !cmd->argv[0])
		{
			if (cmd->delimiter)
			{
				mini->last = 2;
				return;
			}
			ft_redirection(cmd, mini);
			mini->last = 0;
			return ;
		}
		if (cmd->buildtin)
			exec_build(cmd, mini);
		else
			exec_no_build(cmd, mini);
	}
}

