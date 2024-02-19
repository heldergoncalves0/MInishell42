/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:15:36 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/19 12:57:12 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_cmd(t_cmd *cmd, t_shell *s, int in, int out)
{
	(void) in;
	(void) cmd;
	ft_putstr_fd(get_env(s, "PWD"), out);
	ft_putstr_fd("\n", out);
}
//  env | grep PWD oldpwd fica a nulo sem o =
