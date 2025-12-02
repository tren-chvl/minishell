/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:11:47 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:11:05 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_printf.h>

int	handle_p(va_list list)
{
	void			*ptr;
	size_t			size;
	size_t			nbr;

	ptr = va_arg(list, void *);
	if (!ptr)
	{
		putstr_fd("(nil)", 1);
		return (ft_strlen("(nil)"));
	}
	nbr = (size_t)ptr;
	putstr_fd("0x", 1);
	putunsignednbr_base((size_t)nbr, "0123456789abcdef");
	size = 2;
	while (nbr > 0)
	{
		size++;
		nbr /= 16;
	}
	return (size);
}
