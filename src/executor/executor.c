/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:23:24 by helferna          #+#    #+#             */
/*   Updated: 2024/02/20 19:49:27 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_executable_path(char *binary, int i)
{
	char	*tmp;
	char	*command;
	char	**path;

	if (binary != NULL)
	{
		if (access(binary, X_OK) == 0)
			return (ft_strdup(binary));
		path = ft_split(getenv("PATH"), ':');
		while (path[++i])
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
		}
		free_array(path);
	}
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

static void	wait_child(t_shell *s, t_cmd *cmd)
{
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
		cmd->path = find_executable_path(cmd->args[0], -1);
		if (cmd->next && pipe(cmd->fd) == -1)
			exit(1);
		out = cmd->fd[1];
		out = change_outfile(out, cmd->out_file, cmd->fd);
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
