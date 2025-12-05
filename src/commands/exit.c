/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:41:31 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/04 17:48:39 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exit_parsing(t_cmd *cmd)
{
	char	**tab;
	int		operator;
	int		count;

	tab = cmd->argv;
	count = arg_count(cmd);
	operator = 0;
	if (tab[1][0] == '-' || tab[1][0] == '+')
		operator = 1;
	if (!str_isdigit(&tab[1][operator]))
	{
		ft_printferror("exit: %s: numeric argument required\n", tab[1]);
		return (2);
	}
	if (count > 2)
	{
		ft_printferror("exit: too many arguments\n");
		return (-1);
	}
	if (count == 1)
		return (0);
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
	{
		mini->prev_exit = 1;
		return ;
	}
	free_mini(mini);
	exit(code);
}
