/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:48:05 by helferna          #+#    #+#             */
/*   Updated: 2024/02/24 16:15:53 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_something(char **s, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strncmp(s[i], cmd->args[1], ft_strlen(cmd->args[1])) == 0)
		{
			free(s[i]);
			while (s[i + 1] != NULL)
			{
				s[i] = s[i + 1];
				i++;
			}
			s[i] = 0;
		}
		i++;
	}
}

void	unset_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	(void)in;
	(void)out;
	unset_something(s->env, cmd);
	unset_something(s->export, cmd);
}
