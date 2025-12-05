/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:06:31 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/05 11:06:50 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_redir_error(char *path)
{
	ft_printferror("minishell: %s: %s\n", path, strerror(errno));
}
