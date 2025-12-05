/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:09:48 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/04 18:21:26 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	mini_unset(t_mini *mini, t_cmd *cmd)
{
	t_env	*env;
	int		i;

	i = 0;
	while (cmd->argv[++i])
	{
		env = find_env(mini->env, cmd->argv[i]);
		if (!env)
			return ;
		ft_lstdelif(&mini->env, env, free_env);
	}
	free_envp(mini->envp);
	mini->envp = create_envp(mini);
}
