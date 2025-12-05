/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:19:05 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/04 21:20:23 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*redir_error_pipi(t_token *toks, int i, int ntok)
{
	int	k;
	int	adj_count;

	adj_count = 1;
	k = i + 1;
	while (k < ntok && toks[k].type == TOK_PIPE && toks[k].bef == 0)
	{
		adj_count++;
		k++;
	}
	if (adj_count >= 2)
		return ("||");
	if (i == 0 || i + 1 >= ntok)
		return ("|");
	return (NULL);
}

char	*redir_error_token(t_token *toks, int i, int ntok)
{
	if (i + 1 >= ntok)
		return ("newline");
	if (toks[i + 1].type == TOK_WORD)
		return (NULL);
	if (toks[i + 1].type == TOK_PIPE)
		return ("|");
	if (toks[i + 1].val != NULL)
		return (toks[i + 1].val);
	if (toks[i + 1].type == TOK_LT)
		return ("<");
	if (toks[i + 1].type == TOK_GT)
		return (">");
	if (toks[i + 1].type == TOK_GTGT)
		return (">>");
	if (toks[i + 1].type == TOK_LTLT)
		return ("<<");
	return ("newline");
}

char	*check_redir_syntax(t_token *toks, int ntok)
{
	int		i;
	char	*err;

	i = 0;
	while (i < ntok)
	{
		if (toks[i].type == TOK_PIPE)
		{
			err = redir_error_pipi(toks, i, ntok);
			if (err)
				return (err);
		}
		else if (toks[i].type == TOK_GT || toks[i].type == TOK_LT
			|| toks[i].type == TOK_GTGT || toks[i].type == TOK_LTLT)
		{
			err = redir_error_token(toks, i, ntok);
			if (err)
				return (err);
		}
		i++;
	}
	return (NULL);
}

int	check_files(t_cmd *cmd, t_mini *mini)
{
	(void)cmd;
	(void)mini;
	return (0);
}

int	f_ck_redirection(t_cmd *cmd, t_mini *mini, t_token *toks, int ntok)
{
	char	*err;

	(void)cmd;
	err = check_redir_syntax(toks, ntok);
	if (err)
	{
		ft_printferror("minishell: syntax error near unexpected token `%s'\n",
			err);
		mini->prev_exit = 2;
		return (-1);
	}
	return (0);
}
