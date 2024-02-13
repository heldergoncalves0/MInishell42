/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:15:50 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/13 16:54:31 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_list(t_cmd *c)
{
	int	i;

	i = 0;
	if (c == NULL)
		return ;
	printf("====== cmd ======\n");
	while (c->args[i])
		printf("arg:%s\n", c->args[i++]);
	printf("in: %d\n", c->in_file);
	printf("out: %d\n", c->out_file);
	ft_listredir(c->red);
	if (c->next)
		ft_list(c->next);
	printf("\n");
}

void	ft_listredir(t_redir *c)
{
	while (c)
	{
		printf("	====== redir ======\n");
		printf("	name:%s\n", c->args[0]);
		printf("	file:%s\n", c->args[1]);
		printf("	fd: %d\n", c->fd);
		printf("	type: %d\n", c->type);
		c = c->next;
	}

}
