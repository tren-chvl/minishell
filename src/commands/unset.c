/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:09:48 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/25 14:06:44 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_unset(t_mini *mini, char *name)
{
	t_env	*env;

	env = find_env(mini->env, name);
	if (!env)
		return ;
	ft_lstdelif(&mini->env, env, free_env);
}
