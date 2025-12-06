/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:53:51 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/05 14:31:50 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_all_heredocs(t_cmd *cmds)
{
	t_cmd	*cur;
	t_redir	*r;

	cur = cmds;
	while (cur)
	{
		r = cur->redirs;
		while (r)
		{
			if (r->type == R_HEREDOC)
				process_heredoc(r);
			r = r->next;
		}
		cur = cur->next;
	}
}

void	process_heredoc(t_redir *redir)
{
	char	*line;
	char	*tmp;
	char	*new_tmp;

	tmp = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, redir->filename))
		{
			free(line);
			break ;
		}
		if (!redir->quotes)
			str_hasenv(NULL, &line);
		if (!tmp)
			new_tmp = ft_strjoin(line, "\n");
		else
		{
			new_tmp = ft_strjoin(tmp, line);
			new_tmp = ft_strjoin(new_tmp, "\n");
		}
		free(tmp);
		tmp = new_tmp;
		free(line);
	}
	redir->buf_heredoc = tmp;
}
