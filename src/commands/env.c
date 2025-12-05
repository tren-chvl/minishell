/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:47:00 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/04 18:04:59 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_env(t_mini *mini)
{
	t_env	*env;
	t_list	*list;

	list = mini->env;
	if (!list)
		return ;
	while (list)
	{
		env = list->content;
		if (!env)
			continue ;
		if (env->value && env)
			ft_printf("%s=%s\n", env->name, env->value);
		list = list->next;
	}
	mini->prev_exit = 0;
}
