/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:58:02 by helferna          #+#    #+#             */
/*   Updated: 2024/02/25 16:39:30 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	help_builtin(t_cmd *cmd)
{
	if (!cmd->args[0])
		return (-1);
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (2);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (4);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (5);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (6);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (3);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (7);
	return (0);
}

static int	execute_builtin(t_cmd *cmd, t_shell *s, int in, int out)
{
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (cd_cmd(cmd, s, in, out));
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (unset_cmd(cmd, s, in, out));
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (export_cmd(cmd, s, in, out));
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (pwd_cmd(cmd, s, in, out));
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (echo_cmd(cmd, s, 0, out));
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (exit_cmd(cmd, s, in, out));
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (env_cmd(cmd, s, in, out));
	return (0);
}

static int	builtin_execute(t_cmd *cmd, t_shell *s, int in, int out)
{
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		set_signal_action(3);
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		close_fds(in, out);
		close_fds(cmd->fd[0], cmd->fd[1]);
		free_shell(s, execute_builtin(cmd, s, STDIN_FILENO, STDOUT_FILENO));
	}
	set_signal_action(2);
	close_fds(in, out);
	return (1);
}

int	is_builtin(t_cmd *cmd, t_shell *s, int in, int out)
{
	int	is_builtin;

	is_builtin = help_builtin(cmd);
	if (cmd->is_error_redir || is_builtin == 0)
		return (0);
	if (is_builtin != -1)
	{
		if (s->num_cmds > 1 && is_builtin < 5)
			return (builtin_execute(cmd, s, in, out));
		execute_builtin(cmd, s, in, out);
		close_fds(in, out);
		return (1);
	}
	close_fds(in, out);
	return (-1);
}

//env ola