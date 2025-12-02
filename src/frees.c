/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:43:17 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/02 12:51:57 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_token(t_token *token, int nbtok)
{
	int i;

	i = 0;
	while (i < nbtok)
	{
		free(token[i].val);
		i++;
	}
	free(token);
}
void	free_env(void *content)
{
	t_env	*env;

	if (!content)
		return ;
	env = content;
	free(env->name);
	if (env->value)
		free(env->value);
	free(env);
}

void	free_mini(t_mini *mini)
{
	ft_lstclear(&mini->env, free_env);
	free(mini->path);
	free(mini);
	rl_clear_history();
}

void	free_tab(char **tab)
{
	int	i;

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

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		j;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
		{
			j = 0;
			while (cmd->argv[j])
				free(cmd->argv[j++]);
			free(cmd->argv);
		}
		if (cmd->path)
			free(cmd->path);
		free(cmd);
		cmd = tmp;
	}
}
