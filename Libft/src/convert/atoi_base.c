/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:41:54 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 12:51:07 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_convert.h>

int	atoi_base(char *str, char *base)
{
	int	i;
	int	ret;
	int	negative;
	int	len;

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
