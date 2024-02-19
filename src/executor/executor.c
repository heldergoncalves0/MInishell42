/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:23:24 by helferna          #+#    #+#             */
/*   Updated: 2024/02/19 14:57:31 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_executable_path(char *binary)
{
	char	*tmp;
	char	*command;
	int		i;
	char	**path;

	if (access(binary, X_OK) == 0)
		return (ft_strdup(binary));
	path = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		command = ft_strjoin(tmp, binary);
		free(tmp);
		if (access(command, X_OK) == 0)
		{
			free_array(path);
			return (command);
		}
		free(command);
		i++;
	}
	free_array(path);
	return (NULL);
}

void	execute_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	pid_t	pid;
	//int		status;

	if (cmd->is_error_redir == 0 && cmd->args[0] != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			set_signal_action(3);
			dup2(in, STDIN_FILENO);
			close_fd(in);
			dup2(out, STDOUT_FILENO);
			close_fd(out);
			if (cmd->path)
				execve(cmd->path, cmd->args, s->env);
			cmd_not_found_error(cmd->args[0]);
			free_shell(s);
			exit(127);
		}
		set_signal_action(2);
	}
	close_fd(in);
	close_fd(out);
}

void	exit_status(t_cmd *cmd)
{
	while (cmd)
	{
		wait(NULL);
		cmd = cmd->next;
	}
}

void	executor(t_shell *s)
{
	int		in;
	int		out;
	t_cmd	*cmd;

	in = 0;
	cmd = s->cmd;
	while (cmd)
	{
		if (cmd->next && pipe(cmd->fd) == -1)
			exit(1);
		out = cmd->fd[1];
		if (cmd->out_file != -1)
		{
			out = cmd->out_file;
			close_fd(cmd->fd[1]);
		}
		if (cmd->in_file != -1)
			in = cmd->in_file;
		if (!is_builtin_execute(cmd, s, in, out))
			execute_cmd(cmd, s, in, out);
		in = cmd->fd[0];
		cmd = cmd->next;
	}
	cmd = s->cmd;
	exit_status(cmd);
}
// yes | head
