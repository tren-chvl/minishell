/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:06:21 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/01 10:05:32 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



void	exec_commande(char *cmd, char **envp)
{
	char	**split;
	char	*path;

	if (!cmd || !*cmd)
		exit(127);
	split = ft_split_pp(cmd, ' ');
	if (!split || !split[0] || !*split[0])
	{
		ft_free_tab(split);
		exit(127);
	}
	if (ft_strchr(split[0], '/'))
		path = ft_strdup_pp(split[0]);
	else
		path = find_path(split[0], envp);
	safe_execve(path, split, envp);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	int	ret;

// 	if (argc < 5)
// 		return (error_msg("error argument :( "));
// 	if (ft_strcmp_pp(argv[1], "here_doc") == 0)
// 		ret = here_doc(argc, argv, envp);
// 	else
// 		ret = pipex(argc, argv, envp);
// 	return (ret);
// }
