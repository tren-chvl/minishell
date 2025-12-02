/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:56:51 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/02 11:17:57 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_convert.h>
#include <libft_math.h>

char	*itoa_base(int n, char *base)
{
	char	*str;
	int		size;
	int		len;
	int		i;

	size = nbsize_base(n, base);
	len = ft_strlen(base);
	str = malloc(sizeof(char) * (size + 1 + (n < 0) + (n == 0)));
	if (!str)
		return (NULL);
	i = 1;
	if (n == 0)
		str[0] = '0';
	if (n < 0)
		str[--i] = '-';
	str[size + (n < 0) + (n == 0)] = '\0';
	while (n != 0)
	{
		if (n < 0)
			str[size - i] = absolute(n % len) + '0';
		i++;
		n /= len;
	}
	return (str);
}
