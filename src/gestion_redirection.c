/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:19:05 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/02 16:18:07 by marcheva         ###   ########.fr       */
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
	if (k >= ntok)
		return ("|");
	if (toks[k].type == TOK_WORD)
		return (NULL);
	if (adj_count == 2 || adj_count == 3)
		return ("||");
	return ("|");
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
	int	fd;

	if (cmd->intfile)
	{
		fd = open(cmd->intfile, O_RDONLY);
		if (fd == -1)
			return (perror(cmd->intfile), mini->last = 1, -1);
		close(fd);
	}
	if (cmd->outfile)
	{
		if (cmd->append)
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(cmd->outfile);
			mini->last = 1;
			return (-1);
		}
		close(fd);
	}
	return (0);
}

int	f_ck_redirection(t_cmd *cmd, t_mini *mini, t_token *toks, int ntok)
{
	char	*err;

	err = check_redir_syntax(toks, ntok);
	if (err)
	{
		ft_printf("minishell: syntax error near unexpected token `%s'\n", err);
		mini->last = 2;
		return (-1);
	}
	if (check_files(cmd, mini) == -1)
		return (-1);
	return (0);
}

