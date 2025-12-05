/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:38:27 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/05 13:46:31 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_heredoc(t_cmd *cmd, t_mini *mini)
{
	int	fd[2];

	if (!cmd->here_doc)
		return (0);
	if (pipe(fd) == -1)
	{
		perror("minishell");
		return (1);
	}
	str_hasenv(mini, &cmd->here_doc);
	write(fd[1], cmd->here_doc, ft_strlen(cmd->here_doc));
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("minishell");
		close(fd[0]);
		return (1);
	}
	close(fd[0]);
	return (0);
}

int	out_trunc(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_printferror("minishell: %s: %s\n", file, strerror(errno));
		if (fd >= 0)
			close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	out_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_printferror("minishell: %s: %s\n", file, strerror(errno));
		if (fd >= 0)
			close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	in_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0 || dup2(fd, STDIN_FILENO) == -1)
	{
		ft_printferror("minishell: %s: %s\n", file, strerror(errno));
		if (fd >= 0)
			close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	ft_redirection(t_cmd *cmd, t_mini *mini)
{
	t_redir	*r;

	(void)mini;
	r = cmd->redirs;
	while (r)
	{
		if (r->type == R_OUT_TRUNC && out_trunc(r->filename))
			return (1);
		else if (r->type == R_OUT_APPEND && out_append(r->filename))
			return (1);
		else if (r->type == R_IN_FILE && in_file(r->filename))
			return (1);
		else if (r->type == R_HEREDOC && redir_heredoc(cmd, mini))
			return (1);
		r = r->next;
	}
	return (0);
}
