/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:09:16 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:11:01 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_printf.h>

int	handle_s(va_list list)
{
	char	*str;

	str = va_arg(list, char *);
	if (!str)
		str = "(null)";
	putstr_fd(str, 1);
	return (ft_strlen(str));
}
