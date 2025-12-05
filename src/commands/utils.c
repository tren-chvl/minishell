/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:53:54 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/04 16:03:52 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	arg_count(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->argv[i])
		i++;
	return (i);
}

int	too_many_args(t_mini *mini, t_cmd *cmd)
{
	if (arg_count(cmd) > 2)
	{
		perror(strerror(1));
		mini->prev_exit = 1;
		return (1);
	}
	return (0);
}
