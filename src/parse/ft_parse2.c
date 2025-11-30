/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:12:12 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/27 14:04:29 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command(char *line, int *i)
{
	int		start;
	char	*cmd;
	char	*result;

	start = *i;
	while (line[*i] && !ft_signe(line[*i]))
		(*i)++;
	cmd = ft_substr(line, start, *i - start);
	result = ft_strtrim(cmd, "  \r\n\t\v\f");
	return (result);
}

int	is_builtin(char *cmd)
{
	char	*build[8];
	int		i;

	i = 0;
	if (!cmd)
		return (0);
	build[0] = "cd";
	build[1] = "echo";
	build[2] = "env";
	build[3] = "exit";
	build[4] = "export";
	build[5] = "pwd";
	build[6] = "unset";
	build[7] = NULL;
	while (build[i])
	{
		if (!ft_strcmp(cmd, build[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*get_your_word(char *line, int *i)
{
	int		start;
	int		quote;
	char	*word;

	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (!line[*i])
		return (NULL);
	if (line[*i] == '\'' || line[*i] == '\"')
	{
		quote = line[*i];
		start = ++(*i);
		while (line[*i] && line[*i] != quote)
			(*i)++;
		word = ft_substr(line, start, *i - start);
		if (line[*i] == quote)
			(*i)++;
		return (word);
	}
	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && !ft_signe(line[*i]))
		(*i)++;
	word = ft_substr(line, start, *i - start);
	return (word);
}

char	**ft_word(char *line)
{
	char	**argv;
	char	*word;
	int		i;
	int		j;

	i = 0;
	j = 0;
	argv = malloc(sizeof(char *) * (1023) + 1);
	if (!argv)
		return (NULL);
	while (line[i])
	{
		word = get_your_word(line, &i);
		if (word)
			argv[j++] = word;
	}
	argv[j] = NULL;
	return (argv);
}

t_cmd	*parse_command(char **para, t_mini *mini)
{
	t_cmd	*head;
	t_cmd	*tmp;
	int		i;

	head = NULL;
	tmp = NULL;
	i = 0;
	while (para[i])
	{
		t_cmd	*new;
		new = malloc(sizeof(t_cmd));
		if (!new)
			return (NULL);
		ft_bzero(new, sizeof(t_cmd));
		new->argv = ft_word(para[i]);
		new->buildtin = is_builtin(new->argv[0]);
		new->path = NULL;
		if (!new->buildtin && new->argv[0])
			new->path = find_exec(mini, new->argv[0]);
		if (!head)
			head = new;
		else
			tmp->next = new;
		tmp = new;
		i++;
	}
	return (head);
}
