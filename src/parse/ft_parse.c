/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:40:18 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/27 13:32:29 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_signe(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

char	*ft_operator(char *line, int *i)
{
	char	*test;

	if ((line[*i] == '>' && line[*i + 1] == '>')
		|| (line[*i] == '<' && line[*i + 1] == '<'))
	{
		test = ft_substr(line,*i, 2);
		*i += 2;
	}
	else
	{
		test = ft_substr(line, *i, 1);
		(*i)++;
	}
	return (test);
}

char	**tabpara(char *line)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * 1000000);
	if (!tab)
		return (NULL);
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (ft_signe(line[i]))
			tab[j++] = ft_operator(line, &i);
		else
			tab[j++] = get_command(line, &i);
	}
	tab[j] = NULL;
	return (tab);
}
