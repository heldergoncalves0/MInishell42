/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:05:43 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/22 13:36:49 by helferna         ###   ########.fr       */
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
	if (cmd->args[2])
	{
		s->status = 1;
		ft_putstr_ln("exit: too many arguments", 2);
	}
	else if (!str_digit(cmd->args[1]))
	{
		s->status = 2;
		ft_putstr_ln("exit: numeric argument required", 2);
		free_shell(s);
	}
	else if (cmd->args[1])
	{
		s->status = ft_atoi(cmd->args[1]);
		close_fd(in);
		close_fd(out);
		free_shell(s);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		close_fd(in);
		close_fd(out);
		free_shell(s);
	}
}
