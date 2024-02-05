/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:21:18 by helferna          #+#    #+#             */
/*   Updated: 2024/02/05 17:37:55 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_executable_path(char *binary, char **path)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		command = ft_strjoin(tmp, binary);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}
void	executor(char **env)
{
    char *path = getenv("PATH");
	char *full_cmd[] = {"wc", "-l", NULL};
	char **cmd_paths = ft_split(path, ':');
	char *executable_path = NULL;
	
	executable_path = find_executable_path(full_cmd[0], cmd_paths);
	if (execve(executable_path, full_cmd, env) == -1)
		printf("ERROR: EXECVE");
}
