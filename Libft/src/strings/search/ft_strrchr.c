/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:09:56 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 12:44:25 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_string.h>

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	last;
	int	found;

	i = 0;
	found = 0;
	while (s[i])
	{
		if (s[i] == (const char) c)
		{
			last = i;
			found = 1;
		}
		i++;
	}
	if (s[i] == (const char) c)
	{
		last = i;
		found = 1;
	}
	if (found)
		return ((char *)&s[last]);
	else
		return (NULL);
}
