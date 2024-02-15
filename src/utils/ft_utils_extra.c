/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:03:03 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/15 15:44:58 by gcatarin         ###   ########.fr       */
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

void	clean_expand_cmd(t_cmd *c)
{
	size_t	i;
	size_t	j;
	int		flag;

	j = 0;
	i = -1;
	while (c->args[++i])
	{
		if (ft_strncmp(c->args[i], "\2", 2) == 0)
		{
			j = i;
			c->args[i] = 0;
			while (c->args[++i])
			{
				c->args[j++] = c->args[i];
				c->args[i] = 0;
			}
			c->args[j] = 0;
			clean_expand_cmd(c);
			break ;
		}
	}
}
