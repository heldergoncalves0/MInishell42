/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:58:02 by helferna          #+#    #+#             */
/*   Updated: 2024/02/06 17:17:55 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_builtin(char **cmd, t_mini *mini, char **env)
{
	if (ft_strncmp(cmd[0], "cd", 2) == 0)
		cd(mini, "ola/estou/aqui", env);
	if (ft_strncmp(cmd[0], "unset", 5) == 0)
		unset(mini, env, "USER");
	if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		pwd(env);
}
