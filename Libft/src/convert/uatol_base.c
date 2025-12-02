/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uatol_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:39:00 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:06:07 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_convert.h>

size_t	uatol_base(char *str, char *base)
{
	int		i;
	size_t	ret;
	int		negative;
	int		len;

	len = 0;
	while (base[len] != '\0')
		len++;
	i = 0;
	negative = 1;
	ret = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	i--;
	while (str[++i] == '-' || str[i] == '+')
		if (str[i] == '-')
			negative *= -1;
	i--;
	while (strchr_index(base, str[++i]) >= 0)
		ret = ret * len + strchr_index(base, str[i]);
	return (ret * negative);
}
