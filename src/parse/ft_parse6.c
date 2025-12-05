/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:02:50 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/04 17:45:52 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_word(char *line, int *i)
{
	int		start;

	if (!line[*i])
		return (NULL);
	start = *i;
	while (line[*i] && ((!ft_isspace(line[*i]) && !ft_signe(line[*i]))
			|| is_in_quotes(line, *i)))
		(*i)++;
	return (ft_substr(line, start, *i - start));
}

void	add_token(t_tokft *ctx, int type, char *val, int bef)
{
	t_token	*new;
	size_t	old_cap;

	if (*ctx->cap == *ctx->n)
	{
		old_cap = *ctx->cap;
		if (old_cap == 0)
			*ctx->cap = 16;
		else
			*ctx->cap = old_cap * 2;
		new = ft_realloc(*ctx->toks, old_cap, *ctx->cap, sizeof(t_token));
		if (!new)
		{
			free(val);
			return ;
		}
		*ctx->toks = new;
	}
	(*ctx->toks)[*ctx->n].type = type;
	(*ctx->toks)[*ctx->n].val = val;
	(*ctx->toks)[*ctx->n].bef = bef;
	(*ctx->n)++;
}

int	handle_operator(char *line, int *i, int space, t_tokft *ctx)
{
	if (is_in_quotes(line, *i))
		return (*i += 1);
	if (line[*i] == '>' && line[*i + 1] == '>')
		return (*i += 2, add_token(ctx, TOK_GTGT, NULL, space), 1);
	if (line[*i] == '<' && line[*i + 1] == '<')
		return (*i += 2, add_token(ctx, TOK_LTLT, NULL, space), 1);
	if (line[*i] == '|')
		return (*i += 1, add_token(ctx, TOK_PIPE, NULL, space), 1);
	if (line[*i] == '>')
		return (*i += 1, add_token(ctx, TOK_GT, NULL, space), 1);
	if (line[*i] == '<')
		return (*i += 1, add_token(ctx, TOK_LT, NULL, space), 1);
	return (0);
}

t_token	*ft_token(char *line, int *ntok)
{
	t_fttokinit	p;

	p.line = line;
	p.toks = NULL;
	p.cap = 0;
	p.n = 0;
	p.i = 0;
	p.space = 0;
	p.tokctx.toks = &p.toks;
	p.tokctx.n = &p.n;
	p.tokctx.cap = &p.cap;
	while (p.line[p.i])
	{
		p.space = skip_spaces(p.line, &p.i);
		if (!p.line[p.i])
			break ;
		if (!handle_operator(p.line, &p.i, p.space, &p.tokctx))
			add_token(&p.tokctx, TOK_WORD, read_word(p.line, &p.i), p.space);
	}
	*ntok = p.n;
	return (p.toks);
}

void	para_argv(t_cmd *cmd, char *s)
{
	int		len;
	int		i;
	char	**newv;

	len = 0;
	if (cmd->argv)
	{
		while (cmd->argv[len])
			len++;
	}
	newv = malloc(sizeof(char *) * (len + 2));
	if (!newv)
		return ;
	i = 0;
	while (i < len)
	{
		newv[i] = cmd->argv[i];
		i++;
	}
	newv[len] = s;
	newv[len + 1] = NULL;
	free(cmd->argv);
	cmd->argv = newv;
}
