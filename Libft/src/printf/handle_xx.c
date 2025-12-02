/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_xx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:53:27 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:10:53 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_printf.h>

int	handle_xx(va_list list)
{
	unsigned int	nbr;
	int				i;

	nbr = va_arg(list, unsigned int);
	putunsignednbr_base(nbr, "0123456789ABCDEF");
	i = 1;
	while (nbr / 16 > 0)
	{
		i++;
		nbr /= 16;
	}
	return (i);
}
