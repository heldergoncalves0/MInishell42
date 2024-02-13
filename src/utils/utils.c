/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:16:00 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/13 15:21:38 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_array(char **s)
{
	int		len;
	char	**new;
	int		i;

	len = 0;
	while (s[len])
		len++;
	i = -1;
	new = ft_calloc(sizeof(char *), len + 1);
	while (s[++i])
		new[i] = ft_strdup(s[i]);
	return (new);
}

char	*flag_return(int flag, char *new)
{
	if (flag == 0)
		return (new);
	free(new);
	return (NULL);
}

int	ft_double_strlen(char **s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
