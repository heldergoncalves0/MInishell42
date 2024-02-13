/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:52:01 by helferna          #+#    #+#             */
/*   Updated: 2024/02/13 21:53:33 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	int	i;

	i = 0;
	(void) in;
	while (s->env[i] && ft_strncmp(s->env[i], "OLDPWD=", 7))
		i++;
	if (s->env[i])
		printf("%s\n", s->env[i] + 4);
	//set("PWD", cmd->path, s->env);
	i = 0;
	while (s->env[i] && ft_strncmp(s->env[i], "PWD=", 4))
		i++;
	if (s->env[i])
		printf("%s\n", s->env[i] + 4);
}
