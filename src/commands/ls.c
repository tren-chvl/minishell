/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dedavid <dedavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:12:08 by dedavid           #+#    #+#             */
/*   Updated: 2025/11/24 15:51:17 by dedavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	sort_dirs(t_list **dirs)
{
	t_list	*temp;
}*/

void	ls(const char *path)
{
	DIR			*ds;
	T_DIRENT	*dir;
	t_list		*dirs;

	ds = opendir(path);
	if (!ds)
		return ;
	readdir(ds);
	dir = readdir(ds);
	dirs = NULL;
	while (dir)
	{
		dir = readdir(ds);
		if (dir)
			ft_lstadd_back(&dirs, ft_lstnew(dir));
	}
	while (dirs)
	{
		printf("%s", ((T_DIRENT *)dirs->content)->d_name);
		dirs = dirs->next;
		if (dirs)
			printf("  ");
		else
			printf("\n");
	}
}
