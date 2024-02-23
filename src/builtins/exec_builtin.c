/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:58:02 by helferna          #+#    #+#             */
/*   Updated: 2024/02/23 22:54:53 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	help_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (2);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (3);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (4);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (5);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (6);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (7);
	return (0);
}

void	execute_builtin(t_cmd *cmd, t_shell *s, int in, int out)
{
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		cd_cmd(cmd, s, in, out);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		unset_cmd(cmd, s, in, out);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		export_cmd(cmd, s, in, out);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		pwd_cmd(cmd, s, in, out);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		echo_cmd(cmd, s, 0, out);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		exit_cmd(cmd, s, in, out);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		env_cmd(cmd, s, in, out);
}

int	is_builtin_execute(t_cmd *cmd, t_shell *s, int in, int out)
{
	int	is_builtin;

	if (!cmd->args[0] || cmd->is_error_redir)
		return (0);
	is_builtin = help_builtin(cmd);
	if (is_builtin == 0)
		return (0);
	if (s->num_cmds > 1 && is_builtin != 7 && is_builtin != 5)
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			set_signal_action(3);
			dup2(in, STDIN_FILENO);
			dup2(out, STDOUT_FILENO);
			close_fds(in, out);
			close_fds(cmd->fd[0], cmd->fd[1]);
			execute_builtin(cmd, s, in, out);
			free_shell(s, s->status);
		}
		set_signal_action(2);
		close_fds(in, out);
		return (1);
	}
	execute_builtin(cmd, s, in, out);
	close_fds(in, out);
	return (1);
}
