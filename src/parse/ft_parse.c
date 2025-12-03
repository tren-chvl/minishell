/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:40:18 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/02 11:11:28 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_signe(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	char	*build[8];
	int		i;

	i = 0;
	if (!cmd)
		return (0);
	build[0] = "cd";
	build[1] = "echo";
	build[2] = "env";
	build[3] = "exit";
	build[4] = "export";
	build[5] = "pwd";
	build[6] = "unset";
	build[7] = NULL;
	while (build[i])
	{
		if (!ft_strcmp(cmd, build[i]))
			return (1);
		i++;
	}
	return (0);
}

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
