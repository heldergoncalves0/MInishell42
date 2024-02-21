/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:52:01 by helferna          #+#    #+#             */
/*   Updated: 2024/02/21 15:53:28 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_path(t_shell *s)
{
	char	*tmp;

	tmp = NULL;
	set_env(s, "OLDPWD", get_env(s, "PWD"));
	tmp = getcwd(tmp, 0);
	set_env(s, "PWD", tmp);
	free(tmp);
}

void	cd_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	(void)in;
	(void)out;

	if (chdir(cmd->args[1]) == 0)
		handle_path(s);
	else if (chdir(cmd->args[1]) != 0)
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd("\n", 2);
	}
}
