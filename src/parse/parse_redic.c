/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:39:39 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/05 14:23:31 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_outfile(t_cmd *res, t_token *toks, int *i)
{
	res->outfile = toks[*i + 1].val;
	if (toks[*i].type == TOK_GTGT)
	{
		res->append = 1;
		add_redir(res, R_OUT_APPEND, toks[*i + 1].val);
	}
	else
	{
		res->append = 0;
		add_redir(res, R_OUT_TRUNC, toks[*i + 1].val);
	}
	toks[*i + 1].val = NULL;
	(*i)++;
}

void	handle_infile(t_cmd *res, t_token *toks, int *i)
{
	res->intfile = toks[*i + 1].val;
	add_redir(res, R_IN_FILE, toks[*i + 1].val);
	toks[*i + 1].val = NULL;
	(*i)++;
}

void	handle_delimiter(t_cmd *res, t_token *toks, int *i)
{
	res->delimiter = toks[*i + 1].val;
	add_redir(res, R_HEREDOC, toks[*i + 1].val);
	toks[*i + 1].val = NULL;
	(*i)++;
}

void	add_redir(t_cmd *cmd, t_redirtype type, char *filename)
{
	t_redir	*node;
	t_redir	*cur;

	node = ft_calloc(1, sizeof(t_redir));
	if (node == NULL)
		return ;
	node->type = type;
	node->filename = filename;
	node->next = NULL;
	if (cmd->redirs == NULL)
	{
		cmd->redirs = node;
		return ;
	}
	cur = cmd->redirs;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = node;
}

int	has_redir_type(t_redir *list, t_redirtype type)
{
	t_redir	*cur;

	cur = list;
	while (cur != NULL)
	{
		if (cur->type == type)
			return (1);
		cur = cur->next;
	}
	return (0);
}
