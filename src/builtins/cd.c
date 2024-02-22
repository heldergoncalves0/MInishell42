/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:52:01 by helferna          #+#    #+#             */
/*   Updated: 2024/02/22 12:50:38 by helferna         ###   ########.fr       */
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

    if (cmd->args[2])
	{
		s->status = 1;
		ft_putstr_ln("cd: too many arguments", 2);
	}
	else if (chdir(cmd->args[1]) == 0)
		handle_path(s);
	else if (chdir(cmd->args[1]) != 0)
	{
		s->status = 1;
		perror("cd");
	}
}
