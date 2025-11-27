/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:57:38 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/27 16:29:30 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void free_tab(char **tab)
{
	int i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	 free(tab);
}
char	*get_env_value(t_env *env,char *name)
{
	t_env *tmp;

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

char    **get_env_path(t_list *env)
{
	char    *path;
	char    **paths;
	int     i;
	t_list  *tmp;
	t_env   *var;
	char *tmp_str;

	path = NULL;
	tmp = env;
	while (tmp)
	{
		var = (t_env *)tmp->content;
		if (!ft_strcmp(var->name, "PATH"))
		{
			path = var->value;
			break;
		}
		tmp = tmp->next;
	}
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		if (paths[i][ft_strlen(paths[i]) - 1] != '/')
		{
			tmp_str = ft_strjoin(paths[i], "/");
			free(paths[i]);
			paths[i] = tmp_str;
		}
		i++;
	}
	return (paths);
}



char *find_exec(t_mini *mini, char *cmd)
{
	char **path;
	char *test;
	int i;

	if (!cmd)
		return (NULL);
	i = 0;
	path = get_env_path(mini->env);
	while (path && path[i])
	{
		test = ft_strjoin(path[i], cmd);
		if (access(test, X_OK) == 0)
		{
			free_tab(path);
			return (test);
		}
		free(test);
		i++;
	}
	free_tab(path);
	return (NULL);	
}

void exec_no_build(t_cmd *cmd, t_mini *mini)
{
	pid_t	pid;
	int		statut;
	char	*exec;

	exec = find_exec(mini,cmd->argv[0]);
	if (!exec)
	{
		ft_printf("minishell : %s command not found\n",cmd->argv[0]);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		 if (execve(exec, cmd->argv,mini->envp) == -1)
		 {
			perror("execve");
			exit(127);
		 }
	}
	else
		waitpid(pid, &statut, 0);
	free(exec);
}
