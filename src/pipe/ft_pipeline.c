#include "minishell.h"

pid_t run_commands_list(t_cmd *cmd_list, t_mini *mini)
{
	t_cmd *cmd;
	int prev_fd;
	pid_t last_pid;
	int	status;

	cmd = cmd_list;
	prev_fd = STDIN_FILENO;
	while (cmd->next)
	{
		run_middle_list(cmd, &prev_fd, mini);
		cmd = cmd->next;
	}
	last_pid = exec_last_child(prev_fd, cmd, mini);
	while (wait(&status) > 0)
        ;
    mini->last = WEXITSTATUS(status);
	return last_pid;
}

void run_middle_list( t_cmd *cmd, int *prev_fd, t_mini *mini)
{
	int fd[2];
	char *exec;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	if (fork() == 0)
	{
		dup2(*prev_fd,STDIN_FILENO);
		dup2(fd[1],STDOUT_FILENO);
		close(*prev_fd);
		close(fd[0]);
		close(fd[1]);
		ft_redirection(cmd,mini);
		exec = find_exec(mini,cmd->argv[0]);
		if (!exec)
		{
			ft_printf("minishell: %s: command not found\n", cmd->argv[0]);
			exit(127);
		}
		execve(exec, cmd->argv, mini->envp);
		perror("execve");
		exit(127);
	}
	close(*prev_fd);
	close(fd[1]);
	*prev_fd = fd[0];
	wait(NULL);
}

int open_outfile(t_cmd *cmd)
{
	int fd;
	int flags;

	flags = O_WRONLY | O_CREAT;
	if (cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->outfile, flags, 0644);
	if (fd == -1)
	{
		perror("open outfile");
		exit(1);
	}
	return (fd);
}

void last_child(int prev_fd, int outfile, t_cmd *cmd, t_mini *mini)
{
    dup2(prev_fd, STDIN_FILENO);
    dup2(outfile, STDOUT_FILENO);
    close(prev_fd);
    if (outfile != STDOUT_FILENO)
        close(outfile);
    ft_redirection(cmd, mini);

    // ✅ si pas de commande, juste exit(0)
    if (!cmd->argv || !cmd->argv[0])
        exit(0);

    char *exec = find_exec(mini, cmd->argv[0]);
    if (!exec)
    {
        ft_printf("minishell: %s: command not found\n", cmd->argv[0]);
        exit(127);
    }
    execve(exec, cmd->argv, mini->envp);
    perror("execve");
    exit(127);
}


pid_t exec_last_child(int prev, t_cmd *cmd, t_mini *mini)
{
	int outfile;
	pid_t pid;

	if (cmd->outfile)
		outfile = open_outfile(cmd);
	else
		outfile = STDOUT_FILENO;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
		last_child(prev, outfile, cmd, mini);
	close(prev);
	if (outfile != STDOUT_FILENO)
		close(outfile);
	return pid;
}
