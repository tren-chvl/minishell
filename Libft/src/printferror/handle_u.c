/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:49:54 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/03 10:59:03 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_printferror.h>

int	handle_uerror(va_list list)
{
	unsigned int	integer;

	integer = va_arg(list, unsigned int);
	putnbr_fd(integer, 2);
	return (nbsize(integer));
}
