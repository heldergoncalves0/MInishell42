/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:23:24 by helferna          #+#    #+#             */
/*   Updated: 2024/02/12 19:41:50 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_executable_path(char *binary)
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

void	execute_cmd(t_shell *s, int in, int out)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (in != STDIN_FILENO)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (out != STDOUT_FILENO)
		{
			dup2(out, STDOUT_FILENO);
			close(out);
		}
		if (!execute_builtin(s, in, out))
			execve(s->cmd->path, s->cmd->args, s->env);
	}
}

void	executor(t_shell *s)
{
	int		in;
	int		out;
	char	*heredoc_array;
	int		pipe_fd[3];

	in = pipe_fd[2];
	while (s->cmd)
	{
		s->cmd->path = find_executable_path(s->cmd->args[0]);
		out = handle_redir_out(s);
		handle_heredoc(s, search_heredocs(s));
		if (s->cmd->next != NULL)
		{
			pipe(pipe_fd);
			execute_cmd(s, in, pipe_fd[1]);
			close(pipe_fd[1]);
			in = pipe_fd[0];
		}
		else
			execute_cmd(s, in, STDOUT_FILENO);
		s->cmd = s->cmd->next;
	//	close(out);
	}
	while (wait(NULL) > 0);
}
