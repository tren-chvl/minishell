/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:40:18 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/01 11:50:33 by marcheva         ###   ########.fr       */
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