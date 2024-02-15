/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:12:46 by helferna          #+#    #+#             */
/*   Updated: 2024/02/15 13:14:54 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		flag_n_echo(char *s)
{
	int	i;

	i = 0;

	if (s[i] && s[i] == '-')
	{
		i++;
		while (s[i] == 'n')
			i++;
		if (i <= 1)
			return (0);
		else
			return (i);
	}
	else
		return (0);

}

void	echo_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	int	i;
	int	flag;

	(void)s;
	(void)in;
	i = 1;
	flag = 0;
	while (flag_n_echo(cmd->args[i]))
	{
		flag = 1;
		if (cmd->args[++i] == NULL)
			break ;
	}
	while (cmd->args[i])
	{	
		ft_putstr_fd(cmd->args[i++], out);
		if (cmd->args[i])
			ft_putstr_fd(" ", out);
	}
	if (flag == 0)
		ft_putstr_fd("\n", out);
}
