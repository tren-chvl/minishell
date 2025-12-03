/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:09:16 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/03 10:58:59 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_printferror.h>

int	handle_serror(va_list list)
{
	char	*str;

	str = va_arg(list, char *);
	if (!str)
		str = "(null)";
	putstr_fd(str, 2);
	return (ft_strlen(str));
}
