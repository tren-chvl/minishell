/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:28:09 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/03 15:02:18 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_quotes(char *str, int pos)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (str[++i])
	{
		if (i == pos && status == 0)
			return (status);
		if (status == 1 && str[i] == '\'')
			status = 0;
		else if (status == 2 && str[i] == '\"')
			status = 0;
		else if (!status && str[i] == '\'')
			status = 1;
		else if (!status && str[i] == '\"')
			status = 2;
		if (i == pos)
			return (status);
	}
	return (0);
}

void	*ft_realloc(void *ptr, size_t ol_cnt, size_t new_count, size_t el_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_count == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = ft_calloc(new_count, el_size);
	if (!new_ptr)
		return (NULL);
	if (ptr != NULL)
	{
		if (ol_cnt < new_count)
			copy_size = ol_cnt * el_size;
		else
			copy_size = new_count * el_size;
		ft_memcpy(new_ptr, ptr, copy_size);
		free(ptr);
	}
	return (new_ptr);
}

int	skip_spaces(char *line, int *i)
{
	int	space;

	space = 0;
	while (line[*i] && ft_isspace(line[*i]))
	{
		(*i)++;
		space = 1;
	}
	return (space);
}
