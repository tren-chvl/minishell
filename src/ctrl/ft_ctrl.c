/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:52:46 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/27 13:29:43 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signo = 0;

void	ctrl_c(int signe)
{
	g_signo = signe;
	printf("^C\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_back_slash(int signe)
{
	g_signo = signe;
}

int	ctrl_d(t_mini *mini, char *line)
{
	if (!line)
	{
		ft_suicide(mini, 0, NULL);
	}
	return (0);
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = ctrl_c;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = ctrl_back_slash;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
}
