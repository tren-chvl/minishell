/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:57:06 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 12:45:12 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_string.h>

static int	count_words(const char *s, char c)
{
	int	i;
	int	words;

	i = -1;
	words = 0;
	while (s[++i])
	{
		if (c != s[i])
			if (i == 0 || c == s[i - 1])
				words++;
	}
	return (words);
}

static int	helper(const char *s, char c, char **tab, int k)
{
	int	i;

	i = 0;
	while (s[i] && c != s[i])
		i++;
	tab[k] = malloc(sizeof(char) * (i + 1));
	if (!tab[k])
		return (0);
	i = -1;
	while (c != s[++i] && s[i])
		tab[k][i] = s[i];
	tab[k][i] = '\0';
	return (1);
}

static void	*free_tab(char **tab, int i)
{
	while (i--)
		free(tab[i]);
	free(tab);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	int		i;
	int		k;
	int		len;

	if (count_words(s, c) == 0)
	{
		tab = malloc(sizeof(char *) * 1);
		if (!tab)
			return (NULL);
		tab[0] = NULL;
		return (tab);
	}
	tab = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	i = -1;
	k = -1;
	len = ft_strlen(s);
	while (++i < len)
		if (c != s[i] && (i == 0 || c == s[i - 1]))
			if (!(helper(&s[i], c, tab, ++k)))
				return (free_tab(tab, k));
	tab[++k] = NULL;
	return (tab);
}
