/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:14:09 by helferna          #+#    #+#             */
/*   Updated: 2024/02/06 17:18:13 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PWD=", 4))
		i++;
	if (env[i])
		printf("%s\n", env[i] + 4);
}