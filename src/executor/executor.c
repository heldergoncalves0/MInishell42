/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:23:24 by helferna          #+#    #+#             */
/*   Updated: 2024/02/16 12:26:48 by gcatarin         ###   ########.fr       */
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
			if (cmd->path)
				execve(cmd->path, cmd->args, s->env);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			free_shell(s);
			exit(127);
		}
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
