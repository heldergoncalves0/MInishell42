/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:48:05 by helferna          #+#    #+#             */
/*   Updated: 2024/02/15 13:19:26 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	(void)s;
	(void)in;
	(void)out;
	if (!cmd->args[1])
		ft_putstr_fd("not enough arguments", 2);
}
