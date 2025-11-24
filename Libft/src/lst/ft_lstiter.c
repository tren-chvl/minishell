/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:59:29 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:06:43 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_list.h>

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*start;

	if (!lst || !(*f))
		return ;
	start = lst;
	(*f)(lst->content);
	while (lst->next && lst->next != start)
	{
		lst = lst->next;
		(*f)(lst->content);
	}
}
