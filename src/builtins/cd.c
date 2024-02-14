/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:52:01 by helferna          #+#    #+#             */
/*   Updated: 2024/02/14 18:43:11 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	char *pwd;
	char *tmp;

	if (chdir(cmd->args[1]) == 0)
	{
		set_env(s, "OLDPWD", get_env(s, "PWD"));
		tmp = ft_strjoin(get_env(s, "PWD"), "/");
		pwd = ft_strjoin(tmp, cmd->args[1]);
		free(tmp);
		tmp = ft_substr(pwd, 0, ft_strlen(pwd) - 1);
		free(pwd);
		set_env(s, "PWD", tmp);
	}
	else
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd("\n", 2);
	}
	free(tmp);
}
