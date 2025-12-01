/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:02:50 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/01 15:26:20 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_word(char *line, int *i)
{
	int		start;
	int		quote;
	char	*word;

	if (!line[*i])
		return (NULL);
	if (line[*i] == '\'' || line[*i] == '\"')
	{
		quote = line[*i];
		(*i)++;
		start = *i;
		while (line[*i] && line[*i] != quote)
			(*i)++;
		word = ft_substr(line, start, *i - start);
		if (line[*i] == quote)
			(*i)++;
		return (word);
	}
	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && !ft_signe(line[*i]))
		(*i)++;
	return (ft_substr(line, start, *i - start));
}

void	add_token(t_token **toks, int *n, int *cap, int type, char *val)
{
	t_token *new;

	if (*cap == *n)
	{
		if (*cap == 0)
			*cap = 16;
		else
			*cap = *cap * 2;
		new = realloc(*toks, sizeof(t_token) * (*cap));
		if (!new)
			return ;
		*toks = new;
	}
	(*toks)[*n].type = type;
	(*toks)[*n].val = val;
	(*n)++;
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
t_token	*ft_token(char *line, int *ntok)
{
	t_token	*toks;
	int		cap;
	int		n;
	int		i;

	toks = NULL;
	cap = 0;
	n = 0;
	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '>' && line[i + 1] && line[i + 1] == '>')
			(add_token(&toks, &n, &cap, TOK_GTGT, NULL), i += 2);
		else if (line[i] == '<' && line[i + 1] && line[i + 1] == '<')
			(add_token(&toks, &n, &cap, TOK_LTLT, NULL), i += 2);
		else if (line[i] == '|')
			(add_token(&toks, &n, &cap, TOK_PIPE, NULL), i++);
		else if (line[i] == '>')
			(add_token(&toks, &n, &cap, TOK_GT, NULL), i++);
		else if (line[i] == '<')
			(add_token(&toks, &n, &cap, TOK_LT, NULL), i++);
		else
			add_token(&toks, &n, &cap, TOK_WORD, read_word(line, &i));
	}
	*ntok = n;
	return (toks);
}

void	handle_redir(t_cmd *res, t_token *toks, int nbtok, int *i)
{
	if ((toks[*i].type == TOK_GT || toks[*i].type == TOK_GTGT)
		&& *i + 1 < nbtok && toks[*i + 1].type == TOK_WORD)
	{
		res->outfile = toks[*i + 1].val;
		if (toks[*i].type == TOK_GTGT)
			res->append = 1;
		toks[*i + 1].val = NULL;
		(*i)++;
	}
	else if (toks[*i].type == TOK_LT
		&& *i + 1 < nbtok && toks[*i + 1].type == TOK_WORD)
	{
		res->intfile = toks[*i + 1].val;
		toks[*i + 1].val = NULL;
		(*i)++;
	}
	else if (toks[*i].type == TOK_LTLT)
	{
		if (*i + 1 < nbtok && toks[*i + 1].type == TOK_WORD)
		{
			res->delimiter = toks[*i + 1].val;
			toks[*i + 1].val = NULL;
			(*i)++;
		}
	else
		res->delimiter = NULL;
}

}

t_cmd	*parse_command_line(char *line)
{
	int		ntok;
	t_token	*toks;
	t_cmd	*head;
	t_cmd	*cur;
	int		i;

	toks = ft_token(line, &ntok);
	head = NULL;
	cur = NULL;
	i = 0;
	while (i < ntok)
	{
		if (!cur)
		{
			cur = ft_calloc(1, sizeof(t_cmd));
			if (!head)
				head = cur;
		}
		if (toks[i].type == TOK_PIPE)
		{
			cur->next = ft_calloc(1, sizeof(t_cmd));
			cur = cur->next;
		}
		else if (toks[i].type == TOK_WORD)
		{
			para_argv(cur, toks[i].val);
			toks[i].val = NULL;
		}
		else
			handle_redir(cur, toks, ntok, &i);
		i++;
	}
	i = 0;
	while (i < ntok)
	{
		free(toks[i].val);
		i++;
	}
	free(toks);
	return (head);
}
