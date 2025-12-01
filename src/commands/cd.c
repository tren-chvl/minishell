/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:30:37 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/01 15:00:16 by dedavid          ###   ########.fr       */
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
	while (mini->path[i] != '/' && i > 0)
		i--;
	if (i != 0)
		mini->path[i] = 0;
}

void	add_to_path(t_mini *mini, char *str)
{
	int	i;

	i = ft_strlen(mini->path) - 1;
	if (mini->path[i] != '/')
		change_path(mini, ft_strjoin(mini->path, "/"));
	change_path(mini, ft_strjoin(mini->path, str));
}

void	cd(t_mini *mini, char *path)
{
	char	**changes;
	int		i;

	changes = ft_split(path, '/');
	i = -1;
	if (ft_strcmp("~", changes[0]) == 0)
		i++;
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

void	mini_cd(t_mini *mini, t_cmd *cmd)
{
	char	*path;
	char	*old;
	int		i;

	i = 0;
	while (cmd->argv[++i])
	{
		if (i > 1)
		{
			perror(strerror(1));
			mini->prev_exit = 1;
			return ;
		}
	}
	old = ft_strdup(mini->path);
	path = cmd->argv[1];
	if (path[0] == '~')
		change_path(mini, ft_strdup(find_env(mini->env, "HOME")->value));
	if (path[0] == '/')
		change_path(mini, ft_strdup("/"));
	cd(mini, path);
	if (chdir(mini->path) == -1)
	{
		ft_printf("minishell: cd: %s: %s\n", path, strerror(errno));
		free(mini->path);
		mini->path = old;
		mini->prev_exit = errno;
	}
	else
		free(old);
}
