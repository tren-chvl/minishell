/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:48:09 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/03 11:02:57 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_printferror.h>

int	handle_conversionerror(va_list list, char c)
{
	if (c == 'c')
		return (handle_cerror(list));
	if (c == 's')
		return (handle_serror(list));
	if (c == 'd')
		return (handle_derror(list));
	if (c == 'i')
		return (handle_ierror(list));
	if (c == 'u')
		return (handle_uerror(list));
	putchar_fd(c, 2);
	return (1);
}

int	ft_printferror(const char *str, ...)
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
			total += handle_conversionerror(list, str[++i]);
		else
		{
			write(2, &str[i], 1);
			total++;
		}
		i++;
	}
	va_end(list);
	return (total);
}
