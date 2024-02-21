/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:13:26 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/21 10:49:34 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	invalid_name_error(char *s)
{
	ft_putstr_fd("Minishell: export: \'", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}

void	cmd_not_found_error(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": command not found\n", 2);
}

int	invalid_file_error(char *s)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(s, 2);
	return (ft_putstr_fd(": No such file or directory\n", 2));
}

// echo "'$?'"
// cd . | cd ..
// cd .. | ls -----> pwd shouldnt change
// builtins must be executed on child processes
// 
