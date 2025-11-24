/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:57:50 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:04:54 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_convert.h>

static int	base_is_valid(char *base)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	while (base[len] != '\0')
		len++;
	if (strchr_index(base, '-') >= 0
		|| strchr_index(base, '+') >= 0 || len <= 1)
		return (0);
	i = -1;
	while (base[++i] != '\0')
	{
		j = i;
		while (base[++j] != '\0')
		{
			if (base[j] == base[i])
				return (0);
		}
	}
	return (1);
}

char	*convert_base(char *nbr, char *base_from, char *base_to)
{
	int		number;
	char	*str;

	if (!base_is_valid(base_from) || !base_is_valid(base_to))
		return (NULL);
	number = atoi_base(nbr, base_from);
	str = itoa_base(number, base_to);
	return (str);
}
