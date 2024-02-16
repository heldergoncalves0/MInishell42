/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:48:05 by helferna          #+#    #+#             */
/*   Updated: 2024/02/16 17:09:44 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	int	i;

	i = 0;
	(void)in;
	(void)out;
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
