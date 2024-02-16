/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:48:05 by helferna          #+#    #+#             */
/*   Updated: 2024/02/16 13:10:02 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	int	i;

	i = 0;
	(void)in;
	(void)out;
	if (!cmd->args[1])
		ft_putstr_fd("not enough arguments", 2);
	else
	{
		while (s->env[i])
		{
			if (ft_strncmp(s->env[i], cmd->args[1], ft_strlen(cmd->args[1])) == 0)
			{
				free(s->env[i]);
				while (s->env[i + 1] != NULL)
				{
					s->env[i] = s->env[i + 1];
					i++;
				}
				s->env[i] = 0;
			}
			i++;
		}
	}
	
}
