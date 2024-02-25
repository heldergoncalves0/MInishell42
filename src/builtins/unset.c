/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:48:05 by helferna          #+#    #+#             */
/*   Updated: 2024/02/25 16:08:48 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	unset_something(char **s, char *arg)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strncmp(s[i], arg, ft_strlen(arg)) == 0)
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

int	unset_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	int	i;

	i = 1;
	(void)in;
	(void)out;
	while (cmd->args[i])
	{
		unset_something(s->env, cmd->args[i]);
		unset_something(s->export, cmd->args[i]);
		i++;
	}
	return (0);
}
