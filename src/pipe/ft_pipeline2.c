/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:38:27 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/05 11:39:20 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_outfile(t_cmd *cmd)
{
	int	fd;
	int	flags;

	if (!cmd->outfile)
		return (0);
	flags = O_WRONLY | O_CREAT;
	if (cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->outfile, flags, 0644);
	if (fd < 0)
	{
		ft_redir_error(cmd->outfile);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_redir_error(cmd->outfile);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	redir_infile(t_cmd *cmd)
{
	int	fd;

	if (!cmd->intfile)
		return (0);
	fd = open(cmd->intfile, O_RDONLY);
	if (fd < 0)
	{
		ft_redir_error(cmd->intfile);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_redir_error(cmd->intfile);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

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


int ft_redirection(t_cmd *cmd, t_mini *mini)
{
	if (cmd->outfile != NULL)
	{
		if (redir_outfile(cmd) != 0)
			return (1);
	}
	if (cmd->intfile != NULL)
	{
		if (redir_infile(cmd) != 0)
			return (1);
	}
	if (cmd->here_doc != NULL)
	{
		if (redir_heredoc(cmd, mini) != 0)
			return (1);
	}
	return (0);
}



void	update_status(t_mini *mini, pid_t wpid, pid_t last_pid, int status)
{
	if (wpid == last_pid)
	{
		if (WIFEXITED(status))
			mini->prev_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			mini->prev_exit = 128 + WTERMSIG(status);
	}
}