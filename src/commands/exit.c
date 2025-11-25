/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:41:31 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/25 16:02:12 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_suicide(t_mini *mini, int code)
{
	ft_printf("\nexit\n");
	free_mini(mini);
	exit(code);
}
