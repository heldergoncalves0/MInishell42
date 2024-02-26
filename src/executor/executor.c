/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:23:24 by helferna          #+#    #+#             */
/*   Updated: 2024/02/26 13:47:56 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_executable_path(t_shell *s, char *binary, int i)
{
	char	*tmp;
	char	*command;
	char	**path;

	if (binary != NULL)
	{
		if (access(binary, X_OK) == 0)
			return (ft_strdup(binary));
		path = ft_split(get_env(s, "PATH"), ':', 0);
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
	return (ft_strdup(binary));
}

void	execute_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	if (cmd->is_error_redir == 0)
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			set_signal_action(3);
			dup2(in, STDIN_FILENO);
			close_fd(in);
			dup2(out, STDOUT_FILENO);
			close_fd(out);
			close_fds(cmd->fd[0], cmd->fd[1]);
			execve(cmd->path, cmd->args, s->env);
			free_shell(s, cmd_error(cmd->args[0]));
		}
		set_signal_action(2);
	}
	if (cmd->is_error_redir > 0)
		s->status = 257;
	close_fds(in, out);
}

static void	wait_child(t_shell *s)
{
	t_cmd	*c;
	int		status;

	status = 0;
	c = s->cmd;
	while (c)
	{
		if (c->pid != 0)
			waitpid (c->pid, &s->status, 0);
		c = c->next;
	}
	if (WIFEXITED(s->status))
		WEXITSTATUS(s->status);
	while (s->status >= 256)
	{
		status++;
		s->status -= 256;
	}
	s->status = status;
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
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		cmd->path = find_executable_path(s, cmd->args[0], -1);
		if (cmd->next && pipe(cmd->fd) == -1)
			exit(s->status);
		out = cmd->fd[1];
		out = change_outfile(out, cmd->out_file, cmd->fd);
		in = change_infile(in, cmd->in_file);
		if (is_builtin(cmd, s, in, out) == 0)
			execute_cmd(cmd, s, in, out);
		in = cmd->fd[0];
		cmd = cmd->next;
	}
	wait_child(s);
}
