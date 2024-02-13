/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:12:46 by helferna          #+#    #+#             */
/*   Updated: 2024/02/12 18:48:37 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(t_cmd *c)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (ft_strncmp(c->args[i], "-n", 3) == 0)
	{
		flag = 1;
		i++;
	}
	while (c->args[i])
		printf("%s", c->args[i++]);
	if (flag == 0)
		printf("\n");
}
