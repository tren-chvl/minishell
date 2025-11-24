/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:15:02 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/22 13:06:47 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_list.h>

static t_list	*free_all(void *content, t_list **lst, void (*del)(void *))
{
	free(content);
	ft_lstclear(lst, (*del));
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*new_start;
	t_list	*new;
	void	*content;

	if (!lst || !(*f) || !(*del))
		return (NULL);
	start = lst;
	content = (*f)(lst->content);
	new = ft_lstnew(content);
	if (!new)
		return (free_all(content, &new, (*del)));
	new_start = new;
	while (lst->next && lst->next != start)
	{
		lst = lst->next;
		content = (*f)(lst->content);
		new->next = ft_lstnew(content);
		if (!new->next)
			return (free_all(content, &new_start, (*del)));
		new = new->next;
	}
	if (lst->next == start)
		new->next = new_start;
	return (new_start);
}
