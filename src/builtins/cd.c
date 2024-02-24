/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:52:01 by helferna          #+#    #+#             */
/*   Updated: 2024/02/24 19:34:08 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_path(t_shell *s)
{
	char	*tmp;

	tmp = NULL;
	set_env(s->env, "OLDPWD", get_env(s, "PWD"));
	set_env(s->export, "OLDPWD", get_env(s, "PWD"));
	tmp = getcwd(tmp, 0);
	set_env(s->env, "PWD", tmp);
	set_env(s->export, "PWD", tmp);
	free(tmp);
}

void	handle_diacritic(t_shell *s)
{
	char	*tmp;

	tmp = NULL;
	tmp = get_env(s, "HOME");
	chdir(tmp);
	set_env(s->export, "OLDPWD", get_env(s, "PWD"));
	set_env(s->export, "PWD", tmp);
	set_env(s->env, "OLDPWD", get_env(s, "PWD"));
	set_env(s->env, "PWD", tmp);
}

void	cd_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	(void)in;
	(void)out;
	if (cmd->args[1])
	{
		if (cmd->args[2])
		{
			s->status = 1;
			ft_putstr_ln("cd: too many arguments", 2);
		}
		else if (cmd->args[1][0] == '~')
			handle_diacritic(s);
		else if (chdir(cmd->args[1]) == 0)
			handle_path(s);
		else if (chdir(cmd->args[1]) != 0)
		{
			s->status = 1;
			cd_error(cmd->args[1]);
		}
	}
}
