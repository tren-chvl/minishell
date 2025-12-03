/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:39:39 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/03 10:46:39 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_outfile(t_cmd *res, t_token *toks, int *i)
{
	res->outfile = toks[*i + 1].val;
	if (toks[*i].type == TOK_GTGT)
		res->append = 1;
	toks[*i + 1].val = NULL;
	(*i)++;
}

void	handle_infile(t_cmd *res, t_token *toks, int *i)
{
	res->intfile = toks[*i + 1].val;
	toks[*i + 1].val = NULL;
	(*i)++;
}

void	handle_delimiter(t_cmd *res, t_token *toks, int *i)
{
	res->delimiter = toks[*i + 1].val;
	toks[*i + 1].val = NULL;
	(*i)++;
}

void	handle_redir(t_cmd *res, t_token *toks, int nbtok, int *i)
{
	if ((toks[*i].type == TOK_GT || toks[*i].type == TOK_GTGT)
		&& *i + 1 < nbtok && toks[*i + 1].type == TOK_WORD)
		handle_outfile(res, toks, i);
	else if (toks[*i].type == TOK_LT
		&& *i + 1 < nbtok && toks[*i + 1].type == TOK_WORD)
		handle_infile(res, toks, i);
	else if (toks[*i].type == TOK_LTLT
		&& *i + 1 < nbtok && toks[*i + 1].type == TOK_WORD)
		handle_delimiter(res, toks, i);
	else
		res->delimiter = NULL;
}
