/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:05:43 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/15 13:17:12 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	(void)cmd;
	ft_putstr_fd("exit\n", 2);
	close_fd(in);
	close_fd(out);
	free_shell(s);		///args
}
