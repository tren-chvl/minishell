#include "minishell.h"

void free_tab(char **tab)
{
	int i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	 free(tab);
}

void free_cmd(t_cmd *cmd)
{
    t_cmd *tmp;
    int j;

    while (cmd)
    {
        tmp = cmd->next;
        if (cmd->argv)
        {
            j = 0;
            while (cmd->argv[j])
                free(cmd->argv[j++]);
            free(cmd->argv);
        }
        if (cmd->path)
            free(cmd->path);
        free(cmd);
        cmd = tmp;
    }
}
