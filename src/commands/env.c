/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:47:00 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/26 14:16:45 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*add_env(t_mini *mini, char *name, char *value)
{
	t_env	*backup;
	char	*old;
	
	backup = find_env(mini->env, name);
	if (backup)
	{
		old = backup->value;
		backup->value = value;
		return (old);
	}
	ft_lstadd_back(&mini->env, ft_lstnew(envnew(name, value)));
	return (NULL);
}

void	remove_env(t_mini *mini, char *name, char *old, t_list *temp)
{
	t_env	*env;

	if (!old)
	{
		ft_lstdelone(ft_lstlast(mini->env), free_env);
		temp->next = NULL;
		return ;
	}
	env = find_env(mini->env, name);
	env->value = old;
}

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
		if (env->value)
			ft_printf("%s=%s\n", env->name, env->value);
		list = list->next;
	}
}
