/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:03:03 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/16 17:03:36 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_cmd *c, int i)
{
	if (ft_strncmp(c->args[i], ">", 2) == 0)
		return (1);
	else if (ft_strncmp(c->args[i], "<", 2) == 0)
		return (1);
	else if (ft_strncmp(c->args[i], ">>", 3) == 0)
		return (1);
	else if (ft_strncmp(c->args[i], "<<", 3) == 0)
		return (1);
	return (0);
}

char	*ft_strchr_quotes(const char *s, int c)
{
	int	flag;

	flag = 0;
	while (*s)
	{
		if (*s == 39 && flag == 0)
			flag = 1;
		else if ((unsigned char)c == *s && flag == 0)
			return ((char *)s);
		else if (*s == 39)
			flag = 0;
		s++;
	}
	return (0);
}
