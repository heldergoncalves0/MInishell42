/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:15:36 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/15 13:18:40 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	(void) in;
	(void) cmd;
	// if (in != -1)
	// 	ft_putstr_fd("pwd ignoring infile\n", 2); // out or error
	ft_putstr_fd(get_env(s, "PWD"), out);
	ft_putstr_fd("\n", out);
		
}
