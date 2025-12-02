/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:15:28 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 12:45:23 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_string.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	total_len;
	char	*str;

	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (total_len == 1)
	{
		str = malloc(1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	str = malloc(total_len * sizeof(char));
	if (!str)
		return (NULL);
	ft_bzero(str, total_len);
	str = ft_strcat(str, s1);
	str = ft_strcat(str, s2);
	return (str);
}
