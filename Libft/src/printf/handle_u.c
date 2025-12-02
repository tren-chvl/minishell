/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:49:54 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:10:58 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_printf.h>

int	handle_u(va_list list)
{
	unsigned int	integer;

	integer = va_arg(list, unsigned int);
	putnbr_fd(integer, 1);
	return (nbsize(integer));
}
