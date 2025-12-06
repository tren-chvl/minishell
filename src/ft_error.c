/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:06:31 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/05 14:23:48 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_error(char *path)
{
	ft_printferror("minishell: %s: %s\n", path, strerror(errno));
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
			free_tab(cmd->argv);
		if (cmd->path)
			free(cmd->path);
		if (cmd->redirs)
			free_redirs(cmd->redirs);
		free(cmd);
		cmd = tmp;
	}
}
