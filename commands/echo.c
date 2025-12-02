/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:51:34 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/27 17:46:50 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_echo(t_cmd *cmd)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (cmd->argv[++i] && strncmp(cmd->argv[i], "-n", 2) == 0)
		n += 1;
	while (cmd->argv[i])
	{
		if (i != n + 1)
			ft_printf(" ");
		ft_printf("%s", cmd->argv[i]);
		i++;
	}
	if (!n)
		ft_printf("\n");
}
