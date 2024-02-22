/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:13:26 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/22 13:54:11 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	invalid_name_error(t_shell *shell, char *s)
{
	shell->status = 1;
	ft_putstr_fd("Minishell: export: \'", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}

void	cmd_not_found_error(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": command not found\n", 2);
}

int	invalid_file_error(t_shell *shell, char *s1, char *s2)
{
	shell->status = 1;
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_ln(s1, 2);
	return (1);
}

void	ctrl_d_error(char *s)
{
	ft_putstr_fd("Minishell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file (wanted \"", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\")\n", 2);
}

// echo "'$?'"
// cd . | cd ..
// cd .. | ls -----> pwd shouldnt change
// builtins must be executed on child processes
// 
