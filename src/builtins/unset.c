/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:48:05 by helferna          #+#    #+#             */
/*   Updated: 2024/02/06 17:05:01 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset(t_mini	*mini, char **env, char *envar)
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
