/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:17:38 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 12:52:57 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_io.h>

static int	strhas(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

static int	base_is_valid(char *base)
{
	int	i;
	int	j;

	if (strhas(base, '-') || strhas(base, '+') || ft_strlen(base) <= 1)
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

void	putnbr_base(ssize_t nbr, char *base)
{
	ssize_t	len;
	ssize_t	l;

	if (!base_is_valid(base))
		return ;
	len = ft_strlen(base);
	l = nbr;
	if (l < 0)
	{
		putchar_fd('-', 1);
		l *= -1;
	}
	if (l >= len)
	{
		putnbr_base(l / len, base);
		putnbr_base(l % len, base);
		return ;
	}
	putchar_fd(base[l], 1);
}
