/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:28:09 by dedavid           #+#    #+#             */
/*   Updated: 2025/12/02 10:55:41 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
