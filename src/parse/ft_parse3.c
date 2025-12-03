/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:00:50 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/02 11:16:34 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *name)
{
	t_env	*tmp;

	if (!env || !name)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*search_in_path(t_mini *mini, char *cmd)
{
	char	**paths;
	char	*test;
	int		i;

	paths = get_env_path(mini->env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		test = ft_strjoin(paths[i], cmd);
		if (access(test, X_OK) == 0)
		{
			free_tab(paths);
			return (test);
		}
		free(test);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

char	*find_exec(t_mini *mini, char *cmd)
{
	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (search_in_path(mini, cmd));
}
