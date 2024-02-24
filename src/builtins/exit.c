/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:05:43 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/23 21:18:41 by helferna         ###   ########.fr       */
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

void	exit_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	if (cmd->args[1])
	{
		if (cmd->args[2])
		{
			s->status = 1;
			ft_putstr_ln("exit: too many arguments", 2);
		}
		else if (!str_digit(cmd->args[1]))
		{
			ft_putstr_ln("exit: numeric argument required", 2);
			free_shell(s, 2);
		}
		else if (cmd->args[1])
		{
			ft_putstr_fd("exit\n", out);
			close_fds(in, out);
			free_shell(s, ft_atoi(cmd->args[1]));
		}
		return ;
	}
	ft_putstr_fd("exit\n", out);
	close_fds(in, out);
	free_shell(s, s->status);
}
