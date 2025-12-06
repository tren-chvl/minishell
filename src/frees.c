/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:43:17 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/04 18:22:41 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *token, int nbtok)
{
	int	i;

	if (!token)
		return ;
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
	if (mini->save_stdin >= 0)
		close(mini->save_stdin);
	if (mini->save_stdout >= 0)
		close(mini->save_stdout);
	if (mini->save_stderr >= 0)
		close(mini->save_stderr);
	ft_lstclear(&mini->env, free_env);
	free(mini->path);
	free_envp(mini->envp);
	rl_clear_history();
	free(mini);
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

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->filename)
			free(redir->filename);
		if (redir->buf_heredoc)
			free(redir->buf_heredoc);
		free(redir);
		redir = tmp;
	}
}
