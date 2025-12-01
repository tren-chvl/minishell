/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:00:50 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/01 16:43:02 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env,char *name)
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

char *find_exec(t_mini *mini, char *cmd)
{
	char    **paths;
	char    *test;
	int     i;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
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


int commande_not_found(t_cmd *cmd, char *exec, t_mini *mini)
{
	if (!exec)
	{
		ft_printf("minishell : %s: command not found\n",cmd->argv[0]);
		mini->last = 127;
		return (1);
	}
	return (0);
}
void exec_no_build(t_cmd *cmd, t_mini *mini)
{
	pid_t	pid;
	int		statut;
	char	*exec;

	exec = find_exec(mini,cmd->argv[0]);
	if (commande_not_found(cmd, exec, mini))
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		ft_redirection(cmd, mini);
		 if (execve(exec, cmd->argv,mini->envp) == -1)
		 {
			perror("execve");
			return ;
		 }
	}
	else
    {
        waitpid(pid, &statut, 0);
        mini->last = WEXITSTATUS(statut);
	}
	free(exec);
}
