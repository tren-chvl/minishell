/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:53:51 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/04 22:04:09 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_all_heredocs(t_cmd *cmds)
{
	t_cmd	*cur;

	cur = cmds;
	while (cur)
	{
		if (cur->delimiter)
			process_heredoc(cur);
		cur = cur->next;
	}
}

void	process_heredoc(t_cmd *cmd)
{
	char	*line;
	char	*tmp;
	char	*new_tmp;

	tmp = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, cmd->delimiter))
		{
			free(line);
			break ;
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

void	join_adjacent_words(t_token *toks, int *ntok)
{
	int		i;
	int		j;
	char	*joined;

	i = 0;
	while (i < *ntok - 1)
	{
		if (toks[i].type == TOK_WORD && toks[i + 1].type == TOK_WORD
			&& toks[i + 1].bef == 0)
		{
			joined = ft_strjoin(toks[i].val, toks[i + 1].val);
			free(toks[i].val);
			toks[i].val = joined;
			j = i + 1;
			while (j < *ntok - 1)
			{
				toks[j] = toks[j + 1];
				j++;
			}
			(*ntok)--;
			continue ;
		}
		i++;
	}
}
