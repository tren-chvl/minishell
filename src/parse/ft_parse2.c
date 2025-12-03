/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:12:12 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/03 10:44:10 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_all_cmd(t_cmd *cmd, t_mini *mini)
{
	int	f_stin;
	int	f_stdou;

	f_stin = dup(0);
	f_stdou = dup(1);
	ft_redirection(cmd, mini);
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
		if (!cmd->argv || !cmd->argv[0])
		{
			if (cmd->delimiter)
			{
				mini->last = 2;
				return ;
			}
			ft_redirection(cmd, mini);
			mini->last = 0;
			return ;
		}
		exec_all_cmd(cmd, mini);
	}
}

void	run_child(t_cmd *cmd, t_mini *mini, char *exec)
{
	ft_redirection(cmd, mini);
	if (execve(exec, cmd->argv, mini->envp) == -1)
	{
		perror("execve");
		return ;
	}
}

int	commande_not_found(t_cmd *cmd, char *exec, t_mini *mini)
{
	if (!exec)
	{
		ft_printf("minishell : %s: command not found\n", cmd->argv[0]);
		mini->last = 127;
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
		mini->last = WEXITSTATUS(statut);
	}
	free(exec);
}
