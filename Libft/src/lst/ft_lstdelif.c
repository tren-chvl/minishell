/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:12:31 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/27 13:35:57 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_list.h>

void	ft_lstdelif(t_list **list, void *target, void (*del)(void *))
{
	t_list	*curr;
	t_list	*last;
	t_list	*temp;

	last = NULL;
	curr = *list;
	temp = NULL;
	while (curr)
	{
		if (curr->content == target)
		{
			if (!last)
				*list = curr->next;
			else
				last->next = curr->next;
			temp = curr;
		}
		last = curr;
		curr = curr->next;
		if (temp)
		{
			ft_lstdelone(temp, del);
			temp = NULL;
		}
	}
}
