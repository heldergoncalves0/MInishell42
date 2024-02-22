/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:13:24 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/22 14:10:48 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_outfile(int out, int cmd_out, int *fd)
{
	if (cmd_out != -1)
	{
		close_fd(fd[1]);
		return (cmd_out);
	}
	return (out);
}

void	exit_status(t_shell *shell, int status)
{
	shell->status = status;
	exit(shell->status);
}

int	div_status(int status)
{
	while (status >= 256)
		status /= 256;
	return (status);
}
