/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:00:50 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/05 14:23:08 by marcheva         ###   ########.fr       */
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

int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
	{
		if ((st.st_mode & S_IFMT) == S_IFDIR)
			return (1);
	}
	return (0);
}

char	*find_exec(t_mini *mini, char *cmd)
{
	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (is_directory(cmd))
		{
			errno = EISDIR;
			return (NULL);
		}
		if (access(cmd, F_OK) != 0)
		{
			errno = ENOENT;
			return (NULL);
		}
		if (access(cmd, X_OK) != 0)
		{
			errno = EACCES;
			return (NULL);
		}
		return (ft_strdup(cmd));
	}
	return (search_in_path(mini, cmd));
}
