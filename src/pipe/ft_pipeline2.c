/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:38:27 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/01 16:58:48 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redir_outfile(t_cmd *cmd, t_mini *mini)
{
	int fd;
	int flags;

	if (!cmd->outfile)
		return;

	flags = O_WRONLY | O_CREAT;
	if (cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;

	fd = open(cmd->outfile, flags, 0644);
	if (fd < 0)
	{
		perror("open outfile");
		mini->last = 1;
		return;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 outfile");
		close(fd);
		mini->last = 1;
		return;
	}
	close(fd);
}

void redir_infile(t_cmd *cmd, t_mini *mini)
{
	int fd;

	if (!cmd->intfile)
		return;

	fd = open(cmd->intfile, O_RDONLY);
	if (fd < 0)
	{
		perror("open infile");
		mini->last = 1;
		return;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 infile");
		close(fd);
		mini->last = 1;
		return;
	}
	close(fd);
}

void redir_heredoc(t_cmd *cmd, t_mini *mini)
{
	int fd[2];

	if (!cmd->here_doc)
		return;
	if (pipe(fd) == -1)
	{
		perror("pipe heredoc");
		mini->last = 1;
		return;
	}
	if (fork() == 0)
	{
		close(fd[0]);
		write(fd[1], cmd->here_doc, ft_strlen(cmd->here_doc));
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 heredoc");
		close(fd[0]);
		mini->last = 1;
		return;
	}
	close(fd[0]);
	wait(NULL);
}

void ft_redirection(t_cmd *cmd, t_mini *mini)
{
	redir_outfile(cmd, mini);
	redir_infile(cmd, mini);
	redir_heredoc(cmd, mini);
}
