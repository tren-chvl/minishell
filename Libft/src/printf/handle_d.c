/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:34:01 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:11:13 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_printf.h>

int	handle_d(va_list list)
{
	int	digit;

	digit = va_arg(list, int);
	putnbr_fd(digit, 1);
	return (nbsize(digit));
}
