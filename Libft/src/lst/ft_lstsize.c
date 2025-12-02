/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:32:24 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:06:53 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_list.h>

int	ft_lstsize(t_list *lst)
{
	t_list	*start;
	int		i;

	start = lst;
	if (!lst)
		return (0);
	i = 1;
	while (lst->next && lst->next != start)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
