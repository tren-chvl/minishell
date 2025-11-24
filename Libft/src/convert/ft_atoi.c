/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:50:12 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 12:57:55 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_convert.h>

static int	ft_strislonglong(const char *str, size_t negative)
{
	size_t	i;
	size_t	size;

	size = 0;
	while (str[size] && ft_isdigit(str[size]))
		size++;
	if (size > 19)
		return (0);
	if (size < 19)
		return (1);
	i = 1;
	if (negative == 1)
		while (i < 20 && ft_strncmp(str, "9223372036854775807", i) <= 0)
			i++;
	else
		while (i < 20 && ft_strncmp(str, "9223372036854775808", i) <= 0)
			i++;
	return (i - 1 == size);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			negative;
	long long	ret;

	i = 0;
	ret = 0;
	negative = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		negative *= -1;
	else if (str[i] != '+')
		i--;
	while (str[i + 1] == '0')
		i++;
	if (!ft_strislonglong(&str[i + 1], negative))
		return ((negative == 1) * -1);
	while (str[++i] && ft_isdigit(str[i]))
		ret = ret * 10 + (str[i] - '0');
	return ((int) ret * negative);
}
