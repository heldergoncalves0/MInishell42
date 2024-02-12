/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:23:24 by helferna          #+#    #+#             */
/*   Updated: 2024/02/12 16:53:10 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_executable_path(char *binary)
{
	char	*tmp;
	char	*command;
	int		i;
	char 	**path;
	
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

void	handle_heredoc(t_shell *s)
{
	char 	*tmp;
	char 	*hered;
	char 	*line;
	pid_t 	pid;
	int 	pipe_fd[3];

	pipe(pipe_fd);
	hered = ft_calloc(1, sizeof(char));
	while (1)
	{
		line = readline(">");
		if (ft_strncmp(line, s->cmd->args[2], 3) == 0)
		{
			ft_putstr_fd(hered,	pipe_fd[1]);
			free(hered);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		hered = ft_strjoin(hered, tmp);
		free(tmp);
		free(line);
	}
	pid = fork();
	if (pid == 0)
	{
		s->cmd->args[1] = NULL;
		s->cmd->args[2] = NULL;
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		execve(s->cmd->path, s->cmd->args, s->env);
	}
	else if (pid > 0)
	{
		close(pipe_fd[0]);
        close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
	}
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
	int		in = 0;
	int		out = 0;
	int		pipe_fd[3];

	in = pipe_fd[2];
	while (s->cmd)
	{
		s->cmd->path = find_executable_path(s->cmd->args[0]);
		if (ft_strncmp(s->cmd->args[1], "<<", 2) == 0)
			handle_heredoc(s);
		else if (s->cmd->next != NULL)
		{
			pipe(pipe_fd);
			execute_cmd(s, in, pipe_fd[1]);
			close(pipe_fd[1]);
			in = pipe_fd[0];
		}
		else
		    execute_cmd(s, in, STDOUT_FILENO);
		s->cmd = s->cmd->next;
	}
	while (wait(NULL) > 0);
}
