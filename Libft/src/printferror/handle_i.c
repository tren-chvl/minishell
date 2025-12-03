/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_i.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:47:38 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/03 10:58:57 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_printferror.h>

int	handle_ierror(va_list list)
{
	int	integer;

	integer = va_arg(list, int);
	putnbr_fd(integer, 2);
	return (nbsize(integer));
}
