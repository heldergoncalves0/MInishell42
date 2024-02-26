/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:59:49 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/26 14:01:50 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_expansions(char **args, int j, int i)
{
	i = j + 1;
	if (args == NULL)
		return (args);
	free(args[j]);
	while (args && args[i])
	{
		args[j++] = args[i];
		args[j] = NULL;
		i++;
	}
	args[j] = NULL;
	return (args);
}
