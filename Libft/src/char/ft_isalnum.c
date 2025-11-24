/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:20:08 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:05:27 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int character)
{
	if (character >= 'A' && character <= 'Z')
		return (1);
	if (character >= 'a' && character <= 'z')
		return (1);
	if (character >= '0' && character <= '9')
		return (1);
	return (0);
}
