/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbsize_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 13:00:15 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:08:09 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_length.h>

size_t	nbsize_base(ssize_t n, char *base)
{
	size_t	size;
	size_t	len;

	len = ft_strlen(base);
	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		size++;
		n /= len;
	}
	return (size);
}
