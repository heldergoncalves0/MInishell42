/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:58:02 by helferna          #+#    #+#             */
/*   Updated: 2024/02/12 16:36:25 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_shell *s, int in, int out)
{
	int i;
	
	i = 0;
	(void) in;
	(void) out;
	if (ft_strncmp(s->cmd->args[0], "cd", 3) == 0 && ++i)
		cd_cmd(getenv("PWD"), s->env);
	else if (ft_strncmp(s->cmd->args[0], "unset", 6) == 0 && ++i)
		unset_cmd(s->env, s->cmd->args[1]);
	else if (ft_strncmp(s->cmd->args[0], "export", 7) == 0 && ++i)
		export_cmd();
	else if (ft_strncmp(s->cmd->args[0], "pwd", 4) == 0 && ++i)
		pwd_cmd(s->env);
	else if (ft_strncmp(s->cmd->args[0], "echo", 5) == 0 && ++i)
		echo_cmd(s->cmd);
	else if (ft_strncmp(s->cmd->args[0], "exit", 5) == 0 && ++i)
		exit_cmd(s);
	else if (ft_strncmp(s->cmd->args[0], "env", 4) == 0 && ++i)
		env_cmd(s->env);
	return (i);
}
