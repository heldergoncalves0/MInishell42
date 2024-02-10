/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:16:00 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/10 18:23:08 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_array(char **s)
{
	int	len;
	char **new;
	int i;
	
	len = 0;
	while (s[len])
		len++;
	i = -1;
	new = ft_calloc(sizeof(char *), len + 1);
	while (s[++i])
		new[i] = ft_strdup(s[i]);
	return (new);
}

void	ft_list(t_cmd *c)
{
	int	i;

	i = 0;
	if (c == NULL)
		return ;
	printf("====== cmd %d ======\n", c->index);
	while (c->args[i])
		printf("arg:%s\n", c->args[i++]);
	if (c->next)
		ft_list(c->next);
	printf("\n");
}
