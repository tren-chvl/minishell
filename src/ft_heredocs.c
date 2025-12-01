/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:53:51 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/01 16:50:33 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_all_heredocs(t_cmd *cmds)
{
	t_cmd	*cur;

	cur = cmds;
	while (cur)
	{
		if (cur->here_doc)
			process_heredoc(cur);
		cur = cur->next;
	}
}

void	process_heredoc(t_cmd *cmd)
{
	char	*line;
	int		fd;

	if (!cmd->here_doc)
		return ;
	fd = open("/tmp/minishell_here_doc",
			O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd == -1)
		return (perror("open"));
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, cmd->here_doc))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	cmd->intfile = ft_strdup("/tmp/minishell_here_doc");
	cmd->here_doc = NULL;
}
