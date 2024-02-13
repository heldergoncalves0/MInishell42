/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:12:46 by helferna          #+#    #+#             */
/*   Updated: 2024/02/13 20:49:48 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (ft_strncmp(cmd->args[i], "-n", 3) == 0)////-nnnnnnnnnnn
	{
		flag = 1;
		i++;
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
