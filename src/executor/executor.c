/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:23:24 by helferna          #+#    #+#             */
/*   Updated: 2024/02/20 19:06:04 by helferna         ###   ########.fr       */
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
			s->status = 127;
			free_shell(s);
		}
		set_signal_action(2);
	}
	close_fd(in);
	close_fd(out);
}

int	div_status(int status)
{
	while (status >= 256)
		status /= 256;
	return (status);
}

static void	wait_child(t_shell *s, t_cmd *cmd)
{
	(void)s;
	while (cmd)
	{
		waitpid(-1, &s->status, 0);
		cmd = cmd->next;
	}
	s->status = div_status(s->status);
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
		cmd->path = find_executable_path(cmd->args[0]);
		if (cmd->next && pipe(cmd->fd) == -1)
			exit_status(s, 1);
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
	wait_child(s, cmd);
}
// yes | head
