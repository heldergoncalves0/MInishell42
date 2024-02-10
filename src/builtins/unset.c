/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:48:05 by helferna          #+#    #+#             */
/*   Updated: 2024/02/10 19:38:21 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_cmd(char **env, char *envar)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], envar, ft_strlen(envar)))
		i++;
	if (env[i])
	{
		printf("%s\n", env[i]);
        free(env[i]);
		env[i] = NULL;
		printf("%s\n", env[i]);
	}
}
