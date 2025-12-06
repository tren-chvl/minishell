/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:12:12 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/05 16:15:06 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_all_cmd(t_cmd *cmd, t_mini *mini)
{
	int	f_stin;
	int	f_stdou;

	f_stin = dup(0);
	f_stdou = dup(1);
	if (ft_redirection(cmd, mini))
	{
		mini->prev_exit = 1;
		dup2(f_stin, 0);
		dup2(f_stdou, 1);
		close(f_stin);
		close(f_stdou);
		return ;
	}
	if (is_builtin(cmd->argv[0]))
		exec_build(cmd, mini);
	else
		exec_no_build(cmd, mini);
	dup2(f_stin, 0);
	dup2(f_stdou, 1);
	close(f_stin);
	close(f_stdou);
}

void	exec_cmd(t_cmd *cmd, t_mini *mini)
{
	if (cmd->next)
		run_commands_list(cmd, mini);
	else
	{
		if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		{
			if (ft_redirection(cmd, mini))
			{
				mini->prev_exit = 1;
				return ;
			}
			mini->prev_exit = 0;
			return ;
		}
		exec_all_cmd(cmd, mini);
	}
}

void	run_child(t_cmd *cmd, t_mini *mini, char *exec)
{
	if (ft_redirection(cmd, mini))
		exit(mini->prev_exit);
	close_fds();
	if (execve(exec, cmd->argv, mini->envp) == -1)
	{
		if (errno == EACCES || errno == EISDIR)
			exit(126);
		if (errno == ENOENT)
			exit(127);
		exit(127);
	}
}

int	commande_not_found(t_cmd *cmd, char *exec, t_mini *mini)
{
	if (!exec)
	{
		if (errno == EISDIR)
		{
			ft_printferror("minishell: %s: Is a directory\n", cmd->argv[0]);
			mini->prev_exit = 126;
		}
		else if (errno == EACCES)
		{
			ft_printferror("minishell: %s: Permission denied\n", cmd->argv[0]);
			mini->prev_exit = 126;
		}
		else
		{
			ft_printferror("minishell: %s: command not found\n", cmd->argv[0]);
			mini->prev_exit = 127;
		}
		return (1);
	}
	return (0);
}

void	exec_no_build(t_cmd *cmd, t_mini *mini)
{
	pid_t	pid;
	char	*exec;
	int		statut;

	exec = find_exec(mini, cmd->argv[0]);
	if (commande_not_found(cmd, exec, mini))
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(exec);
		return ;
	}
	if (pid == 0)
		run_child(cmd, mini, exec);
	else
	{
		waitpid(pid, &statut, 0);
		if (WIFEXITED(statut))
			mini->prev_exit = WEXITSTATUS(statut);
		else if (WIFSIGNALED(statut))
			mini->prev_exit = 128 + WTERMSIG(statut);
	}
	free(exec);
}
