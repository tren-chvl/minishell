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

void    process_all_heredocs(t_cmd *cmds)
{
	t_cmd   *cur;

	cur = cmds;
	while (cur)
	{
		if (cur->delimiter)
			process_heredoc(cur);
		cur = cur->next;
	}
}

void    process_heredoc(t_cmd *cmd)
{
    char    *line;
    char    *tmp;
    char    *new_tmp;

    tmp = NULL;
    while (1)
    {
        line = readline("> ");
        if (!line || !ft_strcmp(line, cmd->delimiter))
        {
            free(line);
            break;
        }
        if (tmp == NULL)
            new_tmp = ft_strjoin("", line);
        else
            new_tmp = ft_strjoin(tmp, line);
        free(tmp);
        tmp = new_tmp;
        new_tmp = ft_strjoin(tmp, "\n");
        free(tmp);
        tmp = new_tmp;
        free(line);
    }
    cmd->here_doc = tmp;
}





