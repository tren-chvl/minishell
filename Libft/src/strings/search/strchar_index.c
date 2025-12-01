/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchar_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:39:17 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/01 14:09:28 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_string.h>

int	strchr_index(const char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}
