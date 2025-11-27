/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:41:31 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/27 13:40:59 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exit_parsing(t_cmd *cmd)
{
	char	**tab;
	int		i;

	i = 0;
	tab = cmd->argv;
	while (tab[++i])
	{
		if (i == 1 && !str_isdigit(tab[i]))
		{
			ft_printf("exit: %s: numeric argument required\n", tab[i]);
			return (2);
		}
	}
	if (i != 2)
	{
		ft_printf("exit: too many arguments\n");
		return (-1);
	}
	return ((unsigned char) ft_atoi(tab[1]));
}

void	ft_suicide(t_mini *mini, int code, t_cmd *cmd)
{
	if (!cmd)
		ft_printf("\n");
	ft_printf("exit\n");
	if (cmd)
		code = exit_parsing(cmd);
	if (code == -1)
		return ;
	free_mini(mini);
	exit(code);
}
