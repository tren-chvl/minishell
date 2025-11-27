/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:00:50 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/27 16:09:45 by marcheva         ###   ########.fr       */
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
		mini_echo(cmd->argv[1], 0);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		mini_pwd(mini);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		mini_env(mini);
}

void	exec_cmd(t_cmd *cmd, t_mini *mini)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->buildtin)
			exec_build(tmp, mini);
		else
			exec_no_build(tmp,mini);
		tmp = tmp->next;
	}
}
