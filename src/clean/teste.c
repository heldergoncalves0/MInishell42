/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:43:16 by helferna          #+#    #+#             */
/*   Updated: 2024/02/20 16:57:41 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

typedef struct s_cmd{
	char    *cmd;
	pid_t	pid;
    int     status;
	int		exit_status;
	char	*path;
}	t_cmd;

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("HI\n");
		exit(130);
	}
}

void	set_signal_action(int sig_state)
{
	if (sig_state == 0)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
void	exit_status(t_cmd *cmd)
{
	waitpid(cmd->pid, &cmd->status, 0);
	if (WIFEXITED(cmd->status))
	{
		cmd->exit_status = WEXITSTATUS(cmd->status);
		printf("Exit status: %d\n", cmd->exit_status);
	}
}


int main (int ac, char *argv[], char *env[])
{
	static t_cmd cmd;

	cmd.pid = fork();
	if (cmd.pid == 0)
	{
		execl("/bin/sh", "bin/sh", "-c", "ls", NULL);
		exit(EXIT_FAILURE);
	}
	if (cmd.pid > 0)
		exit_status(&cmd);
	return (0);
}
