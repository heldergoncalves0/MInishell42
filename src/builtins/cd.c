/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:52:01 by helferna          #+#    #+#             */
/*   Updated: 2024/02/21 15:23:52 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void *go_one_up(t_shell *s)
{
	size_t	old_size;
	int		n;
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	set_env(s, "OLDPWD", get_env(s, "PWD"));
	set_env(s, "PWD", path);
	//return (path);
}

static void	*handle_path(t_shell *s, char *str)
{
	char	*pwd;
	char	*tmp;

	// if (ft_strncmp(str, "..", 3) == 0)
	// 	go_one_up(s);
	if (chdir(str))
	{
		tmp = NULL;
		set_env(s, "OLDPWD", get_env(s, "PWD"));
		tmp = getcwd(tmp, 0);
		set_env(s, "PWD", tmp);
	}
}

void	cd_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	char	*pwd;
	char	*tmp;
	char    *path;

	tmp = NULL;
	path = NULL;
	(void)in;
	(void)out;

	if (chdir(cmd->args[1]) == 0)
		handle_path(s, cmd->args[1]);
	else if (chdir(cmd->args[1]) != 0)
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd("\n", 2);
	}
	// else if (ft_strncmp(cmd->args[1], ".", 3) == 0)
	
	free(path);
	free(tmp);
}
