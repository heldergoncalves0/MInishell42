/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:58:02 by helferna          #+#    #+#             */
/*   Updated: 2024/02/14 14:16:18 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	execute_builtin(t_cmd *cmd, t_shell *s, int in, int out)
{
	if (!cmd -> args[0])
		return (0);
	if (cmd->is_error_redir)
		return (0);
	// if (ft_strncmp(s->cmd->args[0], "cd", 3) == 0)
	// 	cd_cmd(getenv("PWD"), s->env);
	// else if (ft_strncmp(s->cmd->args[0], "unset", 6) == 0)
	// 	unset_cmd(s->env, s->cmd->args[1]);
	if (ft_strncmp(s->cmd->args[0], "export", 7) == 0)
		export_cmd(cmd, s, in, out);
	// if (ft_strncmp(s->cmd->args[0], "pwd", 4) == 0)
	// 	pwd_cmd(cmd, s, in, out);
	// else if (ft_strncmp(s->cmd->args[0], "echo", 5) == 0)
	// 	echo_cmd(s->cmd);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		exit_cmd(cmd, s, in, out);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		env_cmd(cmd, s, in, out);
	else 
		return (0);
	close_fd(in);
	close_fd(out);
	return (1);
}

int	execute_builtin_init(t_cmd  *cmd, t_shell *s, int in, int out)
{
	pid_t	pid;
	int		status;

	if (cmd->is_error_redir == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(in, STDIN_FILENO);
			close_fd(in);
			dup2(out, STDOUT_FILENO);
			close_fd(out);
			if (!execute_builtin(cmd, s, in, out))
				return (0);
			exit(127);
		}
	}
	close_fd(in);
	close_fd(out);
	return (1);
}
