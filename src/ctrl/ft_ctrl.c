#include "../../includes/minishell.h"

void ctrl_c(int signe)
{
	g_signal = signe;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void ctrl_\\(int signe)
{
	g_signal = signe;
}

int main(void)
{
    struct sigaction sa;

    // Gestion de ctrl-C
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);

    // Gestion de ctrl-\
    sa.sa_handler = sigquit_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGQUIT, &sa, NULL);

    while (1)
    {
        char *line = readline("minishell> ");
        if (!line) // ctrl-D
        {
            printf("exit\n");
            break;
        }
        add_history(line);
        // ... parsing + exécution
        free(line);
    }
    return 0;
}