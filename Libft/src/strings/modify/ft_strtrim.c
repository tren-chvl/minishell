/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:11:04 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 12:45:30 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_string.h>

static int	strhas(char const *s, char const c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	while (strhas(set, s1[i]))
		i++;
	start = i;
	i = ft_strlen(s1) - 1;
	while (strhas(set, s1[i]))
		i--;
	end = i + 1;
	return (ft_substr(s1, start, end - start));
}
