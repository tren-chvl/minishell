/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:04:33 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/25 13:41:53 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_export(t_mini *mini, char *name, char *value)
{
	t_env	*new;

	new = find_env(mini->env, name);
	if (new)
	{
		new->value = value;
		return ;
	}			
	new = malloc(sizeof(t_env));
	new->name = name;
	new->value = value;
	ft_lstadd_back(&mini->env, ft_lstnew(new));
}
