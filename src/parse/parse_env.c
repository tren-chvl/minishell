/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 08:58:38 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/01 16:22:42 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_in_quotes(char *str, int pos)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (str[++i])
	{
		if (i == pos && status == 0)
			return (status);
		if (status == 1 && str[i] == '\'')
			status = 0;
		else if (status == 2 && str[i] == '\"')
			status = 0;
		else if (!status && str[i] == '\'')
			status = 1;
		else if (!status && str[i] == '\"')
			status = 2;
		if (i == pos)
			return (status);
	}
	return (0);
}

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

void	write_env(char **str, int start, int lenght, char *value)
{
	char	*temp;
	char	*new;

	(*str)[start] = '\0';
	temp = ft_strjoin(*str, value);
	new = ft_strjoin(temp, &(*str)[lenght]);
	free(temp);
	free(*str);
	*str = new;
}

void	str_hasenv(t_mini *mini, char **str_ptr)
{
	t_env	*env;
	char	*name;
	char	*str;
	int		start;
	int		i;

	str = *str_ptr;
	start = find_env_symbol(str, 0);
	while (start != -1)
	{
		i = start + 1;
		while (str[++i])
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
				break ;
			if (i == start + 1 && !ft_isalpha(str[i]) && str[i] != '_')
				break ;
		}
		name = ft_substr(str, start + 1, i - start - 1);
		env = find_env(mini->env, name);
		if (env)
			write_env(str_ptr, start, i, env->value);
		else if (ft_strcmp(name, "?") == 0)
			write_env(str_ptr, start, i, ft_itoa(mini->prev_exit));
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
