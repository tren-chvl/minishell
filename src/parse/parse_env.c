/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 08:58:38 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/04 23:07:20 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_env_symbol(char *str, int offset)
{
	int		quote;
	int		i;

	i = -1 + offset;
	if (i >= (int) ft_strlen(str))
		return (-1);
	quote = 1;
	while (str[++i])
	{
		if (quote && str[i] == '$' && is_in_quotes(str, i) != 1)
			return (i);
	}
	return (-1);
}

int	find_end(char *str, int start)
{
	int	i;

	i = start + 1;
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			break ;
		if (i == start + 1 && !ft_isalpha(str[i]) && str[i] != '_')
			break ;
	}
	return (i);
}

void	write_env(t_mini *mini, char **str, int start, char *name)
{
	t_env	*env;
	char	*temp;
	char	*new;
	char	*value;
	int		lenght;

	env = find_env(mini->env, name);
	if (env)
		value = env->value;
	else if (ft_strncmp(name, "?", 1) == 0)
		value = ft_itoa(mini->prev_exit);
	else
		value = ft_strdup("");
	if (ft_strncmp(name, "?", 1) == 0)
		lenght = 2;
	else
		lenght = find_end(*str, start) - start;
	(*str)[start] = '\0';
	temp = ft_strjoin(*str, value);
	new = ft_strjoin(temp, &(*str)[lenght + start]);
	free(temp);
	free(*str);
	if (!env)
		free(value);
	*str = new;
}

void	str_hasenv(t_mini *mini, char **str_ptr)
{
	char	*name;
	char	*str;
	int		start;
	int		i;

	str = *str_ptr;
	start = find_env_symbol(str, 0);
	while (start != -1)
	{
		i = find_end(str, start);
		name = ft_substr(str, start + 1, i - start - 1);
		write_env(mini, str_ptr, start, name);
		free(name);
		str = *str_ptr;
		start = find_env_symbol(str, start + 1);
	}
}

void	replace_env(t_mini *mini, t_token *token, int nbtok)
{
	char	*str;
	int		*to_del;
	int		i;
	int		j;
	int		k;

	k = -1;
	while (++k < nbtok)
	{
		if (!token[k].val)
			continue ;
		str_hasenv(mini, &token[k].val);
		str = token[k].val;
		to_del = malloc(sizeof(int) * ft_strlen(str));
		i = -1;
		j = 0;
		while (str[++i])
			if ((str[i] == '\'' || str[i] == '\"') && !is_in_quotes(str, i))
				to_del[j++] = i;
		while (--j >= 0)
			move_left(str, to_del[j]);
		free(to_del);
	}
}
