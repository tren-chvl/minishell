/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:34:01 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/03 10:58:55 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_printferror.h>

int	handle_derror(va_list list)
{
	int	digit;

	digit = va_arg(list, int);
	putnbr_fd(digit, 2);
	return (nbsize(digit));
}
