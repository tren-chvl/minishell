/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:50:43 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 12:29:34 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_gnl.h>

static int	get_newline(char *str)
{
	int			i;

	i = 0;
	if (ft_strchr(str, '\n'))
		while (str[i] != '\n')
			i++;
	return (i);
}

static void	add_string(char **str, char *to_add)
{
	char		*temp;

	temp = *str;
	*str = ft_strjoin(*str, to_add);
	free(temp);
}

static char	*error_handling(char *str, ssize_t nread)
{
	if (!str[0] || nread == -1)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	ssize_t		nread;
	static char	buffer[BUFFER_SIZE + 1];
	char		*str;
	int			i;

	str = ft_strjoin("", "");
	nread = 1;
	i = get_newline(buffer) + 1;
	while (!ft_strchr(&buffer[i], '\n') && nread > 0)
	{
		add_string(&str, &buffer[i]);
		ft_bzero(buffer, BUFFER_SIZE);
		nread = read(fd, buffer, BUFFER_SIZE);
		i = 0;
	}
	if (nread == 0 || nread == -1)
		return (error_handling(str, nread));
	add_string(&str, &buffer[i]);
	if (ft_strchr(&buffer[i], '\n') && i != 0)
		buffer[get_newline(buffer)] = '0';
	str[get_newline(str) + 1] = '\0';
	return (str);
}
