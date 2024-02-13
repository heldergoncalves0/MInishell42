/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:15:36 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/13 20:52:28 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	int	i;

	i = 0;
	// while (s->env[i] && ft_strncmp(s->env[i], "PWD=", 4))
	// 	i++;
	// if (s->env[i])
	// 	printf("%s\n", env[i] + 4);
}
