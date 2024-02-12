/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:23:24 by helferna          #+#    #+#             */
/*   Updated: 2024/02/12 11:19:32 by helferna         ###   ########.fr       */
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

void	execute_cmd(t_cmd *c, t_shell *s, int in, int out)
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
		if (!execute_builtin(c, s, in, out))
			execve(c->path, c->args, s->env);
	}
}

void	executor(t_shell *s)
{
	t_cmd	*cmd;
	int		in = 0;
	int		out = 0;
	int		pipe_fd[3];

	in = pipe_fd[2];
	cmd = s->cmd;
	while (cmd)
	{
		cmd->path = find_executable_path(cmd->args[0]);
		if (cmd->next != NULL)
		{
			pipe(pipe_fd);
			execute_cmd(cmd, s, in, pipe_fd[1]);
			close(pipe_fd[1]);
			in = pipe_fd[0];
		}
		else
		    execute_cmd(cmd, s, in, STDOUT_FILENO);
		cmd = cmd->next;
	}
	while (wait(NULL) > 0);
}
