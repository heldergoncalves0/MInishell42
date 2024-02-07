/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:23:24 by helferna          #+#    #+#             */
/*   Updated: 2024/02/07 16:30:21 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

bool	is_builtin(char **builtin_list, char *cmd)
{
	int	i;
	
	i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (ft_strncmp(cmd, builtin_list[i], ft_strlen(cmd)) == 0)
			return (true);
		i++;
	}
	return (false);
}

// int	executor(char **env, t_mini *mini)
// {
//     mini->path = getenv("PATH");
// 	char *full_cmd[] = {"ls", "-la", NULL};
// 	mini->cmd_paths = ft_split(mini->path, ':');
// 	char *executable_path = NULL;
	
// 	if (is_builtin((char*[]){"echo", "cd", "pwd", "env", "exit", "export", "unset"}, full_cmd[0]))
// 		exec_builtin(full_cmd, mini, env);
// 	else
// 	{
// 		executable_path = find_executable_path(full_cmd[0], mini->cmd_paths);
// 		if (!executable_path)
// 			perror(full_cmd[0]);
// 		if (!execve(executable_path, full_cmd, env))
// 			perror(full_cmd[0]);
// 	}
// 	return (1);
// }