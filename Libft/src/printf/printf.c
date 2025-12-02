/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:48:09 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:10:46 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_printf.h>

int	handle_conversion(va_list list, char c)
{
	if (c == 'c')
		return (handle_c(list));
	if (c == 's')
		return (handle_s(list));
	if (c == 'p')
		return (handle_p(list));
	if (c == 'd')
		return (handle_d(list));
	if (c == 'i')
		return (handle_i(list));
	if (c == 'u')
		return (handle_u(list));
	if (c == 'x')
		return (handle_x(list));
	if (c == 'X')
		return (handle_xx(list));
	putchar_fd(c, 1);
	return (1);
}

int	ft_printf(const char *str, ...)
{
	int		total;
	int		i;
	va_list	list;

	total = 0;
	i = 0;
	va_start(list, str);
	while (str[i])
	{
		if (str[i] == '%')
			total += handle_conversion(list, str[++i]);
		else
		{
			write(1, &str[i], 1);
			total++;
		}
		i++;
	}
	va_end(list);
	return (total);
}
