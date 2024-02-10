/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:23:24 by helferna          #+#    #+#             */
/*   Updated: 2024/02/10 19:26:32 by gcatarin         ###   ########.fr       */
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
	if (!execute_builtin(c, s, in, out))
		execve(c->path, c->args, s->env);
}

void	executor(t_shell *s)
{
	t_cmd	*cmd;
	int 	in;
	int		out;

	cmd = s->cmd;
	while (cmd)
	{
		cmd->path = find_executable_path(cmd->args[0]);
		execute_cmd(cmd, s, in, out);
		cmd = cmd->next;
	}
}