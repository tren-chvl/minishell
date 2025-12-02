/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:16:24 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/24 17:18:35 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_env(t_mini *mini)
{
	t_env	*env;
	t_list	*list;

	list = mini->env;
	if (!list)
		return ;
	while (list)
	{
		env = list->content;
		ft_printf("%s, %s\n", env->name, env->value);
		list = list->next;
	}
}
