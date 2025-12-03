/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:38:26 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/03 15:44:06 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_tokens(t_token *toks, int ntok, t_cmd **head, t_cmd **cur)
{
	int	i;

	i = 0;
	while (i < ntok)
	{
		if (!*cur)
		{
			*cur = ft_calloc(1, sizeof(t_cmd));
			if (!*head)
				*head = *cur;
		}
		if (toks[i].type == TOK_PIPE)
		{
			(*cur)->next = ft_calloc(1, sizeof(t_cmd));
			*cur = (*cur)->next;
		}
		else if (toks[i].type == TOK_WORD)
		{
			para_argv(*cur, toks[i].val);
			toks[i].val = NULL;
		}
		else
			handle_redir(*cur, toks, ntok, &i);
		i++;
	}
}

t_cmd	*parse_command_line(char *line)
{
	int		ntok;
	t_token	*toks;
	t_cmd	*head;
	t_cmd	*cur;

	head = NULL;
	cur = NULL;
	toks = ft_token(line, &ntok);
	parse_tokens(toks, ntok, &head, &cur);
	free_token(toks, ntok);
	return (head);
}
