/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:47:00 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/25 11:06:40 by dedavid          ###   ########.fr       */
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
		ft_printf("%s=%s\n", env->name, env->value);
		list = list->next;
	}
}
