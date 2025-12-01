/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:46:53 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/01 13:54:03 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_convert.h>

char	*ft_itoa(int n)
{
	char			*str;
	int				size;
	int				i;

	size = nbsize(n);
	str = malloc(sizeof(char) * (size + 1 + (n < 0) + (n == 0)));
	if (!str)
		return (NULL);
	i = 1;
	if (n == 0)
		str[0] = '0';
	if (n < 0)
		str[--i] = '-';
	str[size + (n < 0)] = '\0';
	while (n != 0)
	{
		if (n < 0)
			str[size - i] = n % 10 * -1 + '0';
		else
			str[size - i] = n % 10 + '0';
		i++;
		n /= 10;
	}
	return (str);
}
