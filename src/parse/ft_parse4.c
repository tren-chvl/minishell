/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:57:38 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/01 13:58:43 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *get_path_value(t_list *env)
{
	t_env	*var;

	while (env)
	{
		var = (t_env *)env->content;
		if (!ft_strcmp(var->name, "PATH"))
			return (var->value);
		env = env->next;
	}
	return (NULL);
}
void normal_path(char **paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
		{
			tmp = ft_strjoin(paths[i], "/");
			free(paths[i]);
			paths[i] = tmp;
		}
		i++;
	}
}
char	**get_env_path(t_list *env)
{
	char	*path;
	char	**paths;

	path = get_path_value(env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	normal_path(paths);
	return (paths);
}
