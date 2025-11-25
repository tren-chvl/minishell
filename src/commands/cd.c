/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:30:37 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/25 14:08:27 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	change_path(t_mini *mini, char *path)
{
	free(mini->path);
	mini->path = path;
}

void	go_back(t_mini *mini)
{
	int	i;

	i = ft_strlen(mini->path);
	while (mini->path[i] != '/' && i < 0)
		i--;
	mini->path[i] = 0;
}

void	add_to_path(t_mini *mini, char *str)
{
	change_path(mini, ft_strjoin(mini->path, "/"));
	change_path(mini, ft_strjoin(mini->path, str));
}

void	cd(t_mini *mini, char *path)
{
	char	**changes;
	int		i;
	
	changes = ft_split(path, '/');
	i = -1;
	while (changes[++i])
	{
		if (ft_strcmp(".", changes[i]) == 0)
			continue ;
		else if (ft_strcmp("..", changes[i]) == 0)
			go_back(mini);
		else
			add_to_path(mini, changes[i]);
	}
}

void	mini_cd(t_mini *mini, char *path)
{
	if (ft_strcmp("~", path) == 0)
		change_path(mini, ft_strdup(find_env(mini->env, "HOME")->value));
	else if (ft_strcmp("/", path) == 0)
		change_path(mini, ft_strdup("/"));
	else
		cd(mini, path);
	chdir(mini->path);
}
