/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:23:57 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/04 18:50:55 by dedavid          ###   ########.fr       */
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

char	**create_envp(t_mini *mini)
{
	t_list	*list;
	t_env	*env;
	char	**envp;
	char	*temp;
	int		i;

	i = 0;
	envp = malloc(sizeof(char *) * (ft_lstsize(mini->env) + 1));
	list = mini->env;
	while (list)
	{
		env = list->content;
		temp = ft_strjoin(env->name, "=");
		envp[i] = temp;
		if (env->value)
		{
			envp[i] = ft_strjoin(temp, env->value);
			free(temp);
		}
		i++;
		list = list->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	free_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
}
