/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:23:57 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/01 08:51:36 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env(t_list *list, char *name)
{
	t_env	*env;

	if (!list)
		return (NULL);
	while (list)
	{
		env = list->content;
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		list = list->next;
	}
	return (NULL);
}

t_env	*envnew(char *name, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	return (new);
}

void	fill_env(t_mini *mini, char **envp)
{
	t_list	*env;
	int		i;
	int		j;

	env = NULL;
	i = -1;
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j] != '=' && envp[i][j])
			j++;
		if (envp[i][j] == '=')
		{
			envp[i][j] = 0;
			ft_lstadd_back(&env, ft_lstnew(envnew(envp[i], &envp[i][++j])));
		}
		else
			ft_lstadd_back(&env, ft_lstnew(envnew(envp[i], NULL)));
	}
	mini->env = env;
}
