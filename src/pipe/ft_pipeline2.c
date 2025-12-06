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

int	apply_heredoc(t_redir *r, t_mini *mini)
{
	int	fd[2];

	if (!r->buf_heredoc)
		return (0);
	if (pipe(fd) == -1)
	{
		perror("minishell");
		return (1);
	}
	if (!r->quotes)
		str_hasenv(mini, &r->buf_heredoc);
	write(fd[1], r->buf_heredoc, ft_strlen(r->buf_heredoc));
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

int	ft_redirection(t_cmd *cmd, t_mini *mini)
{
	t_redir	*r;
	t_redir	*last_hdoc;

	last_hdoc = NULL;
	r = cmd->redirs;
	while (r)
	{
		if (r->type == R_OUT_TRUNC)
		{
			if (out_trunc(r->filename))
				return (1);
		}
		else if (r->type == R_OUT_APPEND)
		{
			if (out_append(r->filename))
				return (1);
		}
		else if (r->type == R_IN_FILE)
		{
			if (in_file(r->filename))
				return (1);
		}
		else if (r->type == R_HEREDOC)
		{
			last_hdoc = r;
		}
		r = r->next;
	}
	if (last_hdoc)
	{
		if (apply_heredoc(last_hdoc, mini))
			return (1);
	}
	return (0);
}
