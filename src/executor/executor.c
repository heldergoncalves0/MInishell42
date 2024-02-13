/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:23:24 by helferna          #+#    #+#             */
/*   Updated: 2024/02/13 20:27:30 by gcatarin         ###   ########.fr       */
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

void	execute_cmd(t_cmd  *cmd, t_shell *s, int in, int out)
{
	pid_t	pid;
	int		status;

	if (cmd->is_error_redir == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(in, STDIN_FILENO);
			if (in != STDIN_FILENO)
				close(in);
			dup2(out, STDOUT_FILENO);
			if (out != STDOUT_FILENO)
				close(out);
			execve(cmd->path, cmd->args, s->env);
			exit(127);
		}
	}
	if (in != STDIN_FILENO)
		close(in);
	if (out != STDOUT_FILENO)
		close(out);
}

void	executor(t_shell *s)
{
	int		in;
	int		out;
	t_cmd 	*cmd;

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
			if (cmd->fd[1] != 1)
				close(cmd->fd[1]);
		}
		if (cmd->in_file != -1)
			in = cmd->in_file;
		if (!execute_builtin(cmd, s, in, out))
			execute_cmd(cmd, s, in, out);
		in = cmd->fd[0];
		cmd = cmd->next;
	}
	cmd = s->cmd;
	while (cmd)
	{
		wait(NULL);
		cmd = cmd->next;
	}
}
