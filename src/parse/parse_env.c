/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 08:58:38 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/03 11:52:27 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_env_symbol(char *str, int offset)
{
	int		quote;
	int		i;

	i = -1 + offset;
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
	else if (ft_strcmp(name, "?") == 0)
		value = ft_itoa(mini->prev_exit);
	else
		return ;
	lenght = find_end(*str, start) - start;
	(*str)[start] = '\0';
	temp = ft_strjoin(*str, value);
	new = ft_strjoin(temp, &(*str)[lenght]);
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

void	replace_env(t_mini *mini, t_cmd *cmd)
{
	int		i;

	i = -1;
	while (cmd)
	{
		if (!cmd->argv)
		{
			cmd = cmd->next;
			continue ;
		}
		i = -1;
		while (cmd->argv[++i])
			str_hasenv(mini, &cmd->argv[i]);
		cmd = cmd->next;
	}
}
