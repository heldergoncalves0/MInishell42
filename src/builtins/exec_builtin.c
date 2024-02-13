/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:58:02 by helferna          #+#    #+#             */
/*   Updated: 2024/02/13 21:10:39 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_cmd *cmd, t_shell *s, int in, int out)
{
	if (cmd->is_error_redir)
		return (0);



	// if (ft_strncmp(s->cmd->args[0], "cd", 3) == 0)
	// 	cd_cmd(getenv("PWD"), s->env);
	// else if (ft_strncmp(s->cmd->args[0], "unset", 6) == 0)
	// 	unset_cmd(s->env, s->cmd->args[1]);
	// else if (ft_strncmp(s->cmd->args[0], "export", 7) == 0)
	// 	export_cmd();
	// if (ft_strncmp(s->cmd->args[0], "pwd", 4) == 0)
	// 	pwd_cmd(cmd, s, in, out);
	// else if (ft_strncmp(s->cmd->args[0], "echo", 5) == 0)
	// 	echo_cmd(s->cmd);
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		exit_cmd(cmd, s, in, out);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		env_cmd(cmd, s, in, out);
	else 
		return (0);
	close_fd(in);
	close_fd(out);
	return (1);
}
