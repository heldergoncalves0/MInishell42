/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:58:02 by helferna          #+#    #+#             */
/*   Updated: 2024/02/19 15:03:27 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_execute(t_cmd *cmd, t_shell *s, int in, int out)
{
	if (!cmd->args[0] || cmd->is_error_redir)
		return (0);
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		cd_cmd(cmd, s, in, out);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		unset_cmd(cmd, s, in, out);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		export_cmd(cmd, s, in, out);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		pwd_cmd(cmd, s, in, out);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		echo_cmd(cmd, s, 0, out);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		exit_cmd(cmd, s, in, out);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		env_cmd(cmd, s, in, out);
	else 
		return (0);
	close_fd(in);
	close_fd(out);
	return (1);
}
