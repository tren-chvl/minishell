/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:32:25 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/26 14:34:58 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	swap_last(t_mini *mini)
{
	t_list	*last;
	t_list	*last1;
	t_list	*last2;

	last = ft_lstlast(mini->env);
	last1 = mini->env;
	last2 = mini->env;
	while (last1->next != last)
		last1 = last1->next;
	while (last2->next != last1)
		last2 = last2->next;
	last1->next = NULL;
	last->next = last1;
	last2->next = last;
}

t_env	*get_lowest(t_list *list)
{
	t_env	*low;
	t_env	*env;

	env = list->content;
	low = env;
	while (list->next)
	{
		env = list->content;
		if (strcmp(low->name, env->name) > 0)
			low = env;
		list = list->next;
	}
	return (low);
}

t_env	*get_highest(t_list *list)
{
	t_env	*high;
	t_env	*env;

	env = list->content;
	high = env;
	while (list->next)
	{
		env = list->content;
		if (strcmp(high->name, env->name) < 0)
			high = env;
		list = list->next;
	}
	return (high);
}

void	print_env_alpha(t_mini *mini)
{
	t_env	*low;
	t_env	*high;
	t_env	*env;
	t_list	*list;
	int		size;

	low = get_lowest(mini->env);
	size = ft_lstsize(mini->env);
	while (--size > 0)
	{
		if (low->value)
			ft_printf("declare -x %s=\"%s\"\n", low->name, low->value);
		else
			ft_printf("declare -x %s\n", low->name);
		list = mini->env;
		high = get_highest(mini->env);
		while (list->next)
		{
			env = list->content;
			if (strcmp(low->name, env->name) < 0 && strcmp(high->name, env->name) > 0)
				high = env;
			list = list->next;
		}
		low = high;
	}
}
