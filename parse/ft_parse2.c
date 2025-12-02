/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:12:12 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/02 11:37:41 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_build(t_cmd *cmd, t_mini *mini)
{
	if (!cmd)
		return ;
	if (!ft_strcmp(cmd->argv[0], "cd"))
		mini_cd(mini, cmd);
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

void	exec_cmd(t_cmd *cmd, t_mini *mini)
{
	int f_stin;
	int f_stdou;

	if (cmd->next)
		run_commands_list(cmd, mini);
	else
	{
		if (!cmd->argv || !cmd->argv[0])
		{
			if (cmd->delimiter)
			{
				mini->last = 2;
				return ;
			}
			ft_redirection(cmd, mini);
			mini->last = 0;
			return ;
		}
		f_stin = dup(0);
		f_stdou = dup(1);
		ft_redirection(cmd,mini);
		if (is_builtin(cmd->argv[0]))
			exec_build(cmd, mini);
		else
			exec_no_build(cmd, mini);
		dup2(f_stin, 0);
   		dup2(f_stdou, 1);
    	close(f_stin);
    	close(f_stdou);
	}
}
