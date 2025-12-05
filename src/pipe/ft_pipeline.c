/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:18:28 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/04 21:29:52 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	run_commands_list(t_cmd *cmd_list, t_mini *mini)
{
	t_cmd	*cmd;
	int		prev_fd;
	pid_t	last_pid;
	int		status;
	pid_t	wpid;

	cmd = cmd_list;
	prev_fd = STDIN_FILENO;
	while (cmd->next)
	{
		run_middle_list(cmd, &prev_fd, mini);
		cmd = cmd->next;
	}
	last_pid = exec_last_child(prev_fd, cmd, mini);
	wpid = wait(&status);
	while (wpid > 0)
	{
		update_status(mini, wpid, last_pid, status);
		wpid = wait(&status);
	}
	return (last_pid);
}

void	child_middle(t_cmd *cmd, int *prev_fd, int fd[2], t_mini *mini)
{
	char	*exec;

	if (ft_redirection(cmd, mini))
		exit(1);
	if (!cmd->here_doc && !cmd->intfile && *prev_fd != STDIN_FILENO)
		dup2(*prev_fd, STDIN_FILENO);
	if (!cmd->outfile)
		dup2(fd[1], STDOUT_FILENO);
	if (*prev_fd != STDIN_FILENO)
		close(*prev_fd);
	close(fd[0]);
	close(fd[1]);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	exec = find_exec(mini, cmd->argv[0]);
	if (!exec)
	{
		ft_printferror("minishell: %s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	execve(exec, cmd->argv, mini->envp);
	perror("execve");
	exit(127);
}

void	run_middle_list(t_cmd *cmd, int *prev_fd, t_mini *mini)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("minishell");
		mini->prev_exit = 1;
		return ;
	}
	if (fork() == 0)
		child_middle(cmd, prev_fd, fd, mini);
	if (*prev_fd != STDIN_FILENO)
		close(*prev_fd);
	close(fd[1]);
	*prev_fd = fd[0];
}

void	last_child(int prev_fd, t_cmd *cmd, t_mini *mini)
{
	char	*exec;

	if (ft_redirection(cmd, mini))
		exit(1);
	if (!cmd->here_doc && !cmd->intfile && prev_fd != STDIN_FILENO)
		dup2(prev_fd, STDIN_FILENO);
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	exec = find_exec(mini, cmd->argv[0]);
	if (!exec)
	{
		ft_printferror("minishell: %s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	execve(exec, cmd->argv, mini->envp);
	perror("execve");
	exit(127);
}

pid_t	exec_last_child(int prev, t_cmd *cmd, t_mini *mini)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		mini->prev_exit = 1;
		return (-1);
	}
	if (pid == 0)
		last_child(prev, cmd, mini);
	if (prev != STDIN_FILENO)
		close(prev);
	return (pid);
}
