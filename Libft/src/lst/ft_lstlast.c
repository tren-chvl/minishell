/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:36:07 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:06:45 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_list.h>

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*start;

	if (!lst)
		return (NULL);
	start = lst;
	while (lst->next && lst->next != start)
		lst = lst->next;
	return (lst);
}
