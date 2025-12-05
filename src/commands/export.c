/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:04:33 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/04 23:10:28 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	actually_export(t_mini *mini, char *name, char *value)
{
	t_env	*new;

	if (!name && !value)
	{
		print_env_alpha(mini);
		return ;
	}
	new = find_env(mini->env, name);
	if (new)
	{
		free(name);
		if (value)
		{
			free(new->value);
			new->value = value;
		}
		return ;
	}
	new = malloc(sizeof(t_env));
	new->name = name;
	new->value = value;
	ft_lstadd_back(&mini->env, ft_lstnew(new));
	swap_last(mini);
	free_envp(mini->envp);
	mini->envp = create_envp(mini);
}

int	name_isvalid(char *str)
{
	int	i;
	int	s;
	int	d;

	if (ft_isdigit(str[0]))
		return (0);
	i = -1;
	s = 0;
	d = 0;
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_'
			&& str[i] != '\'' && str[i] != '\"')
			return (0);
		if (str[i] == '\'')
			s++;
		if (str[i] == '\"')
			d++;
	}
	if (s % 2 == 0 && d % 2 == 0)
		return (1);
	return (0);
}

int	get_end(char *str, char stop)
{
	int		i;
	int		s;
	int		d;

	i = -1;
	s = -1;
	d = -1;
	while (str[++i])
	{
		if (i == 0 && str[i] == stop)
			continue ;
		if (str[i] == '\'')
			s *= -1;
		if (str[i] == '\"')
			d *= -1;
		if (str[i] == stop && s && d)
			return (i);
	}
	return (i);
}

void	mini_export(t_mini *mini, t_cmd *cmd)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (cmd->argv[++i])
	{
		name = ft_substr(cmd->argv[i], 0, get_end(cmd->argv[i], '='));
		if (cmd->argv[i][get_end(cmd->argv[i], '=')] != '\0')
			value = ft_substr(cmd->argv[i], get_end(cmd->argv[i], '=') + 1,
					get_end(cmd->argv[i], '\0'));
		else
			value = NULL;
		if (!name_isvalid(name))
		{
			ft_printferror("export: '%s': not a valid identifier\n", name);
			mini->prev_exit = 1;
			free(name);
			free(value);
			continue ;
		}
		actually_export(mini, name, value);
	}
	if (i == 1)
		print_env_alpha(mini);
}
