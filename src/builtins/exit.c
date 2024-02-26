/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:05:43 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/26 14:02:14 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	if (cmd->args[1])
	{
		if (cmd->args[2])
		{
			ft_putstr_ln("exit\nexit: too many arguments", 2);
			close_fds(in, out);
			return (257);
		}
		else if (str_digit(cmd->args[1]) == 0)
		{
			ft_putstr_ln("exit\nMinishell: exit: numeric argument required", 2);
			close_fds(in, out);
			free_shell(s, 258);
		}
		ft_putstr_fd("exit\n", out);
		close_fds(in, out);
		free_shell(s, 256 + ft_atoi(cmd->args[1]));
	}
	if (s->num_cmds == 1)
		ft_putstr_fd("exit\n", out);
	close_fds(in, out);
	free_shell(s, 0);
	return (0);
}
