/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:57:23 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/03 10:58:50 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_printferror.h>

int	handle_cerror(va_list list)
{
	char	c;

	c = va_arg(list, int);
	putchar_fd(c, 2);
	return (1);
}
