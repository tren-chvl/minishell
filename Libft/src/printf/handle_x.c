/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:51:29 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:10:55 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_printf.h>

int	handle_x(va_list list)
{
	unsigned int	nbr;
	int				i;

	nbr = va_arg(list, unsigned);
	putunsignednbr_base(nbr, "0123456789abcdef");
	i = 1;
	while (nbr / 16 > 0)
	{
		i++;
		nbr /= 16;
	}
	return (i);
}
