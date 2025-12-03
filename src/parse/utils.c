/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:28:09 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/02 10:55:41 by dedavid          ###   ########.fr       */
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

void    *ft_realloc(void *ptr, size_t old_count, size_t new_count, size_t elem_size)
{
	void    *new_ptr;
	size_t  copy_size;

	if (ptr == NULL)
		return (malloc(new_count * elem_size));
	if (new_count == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_count * elem_size);
	if (new_ptr == NULL)
		return (NULL);
	if (old_count < new_count)
		copy_size = old_count * elem_size;
	else
		copy_size = new_count * elem_size;
	memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}
int skip_spaces(char *line, int *i)
{
	int space;

	space = 0;
	while (line[*i] && ft_isspace(line[*i]))
	{
		(*i)++;
		space = 1;
	}
	return (space);
}
