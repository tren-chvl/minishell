/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:43:17 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/25 15:07:43 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_env(void *content)
{
	t_env	*env;

	if (!content)
		return ;
	env = content;
	free(env->name);
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
