/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_i.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:47:38 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:11:11 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_printf.h>

int	handle_i(va_list list)
{
	int	integer;

	integer = va_arg(list, int);
	putnbr_fd(integer, 1);
	return (nbsize(integer));
}
