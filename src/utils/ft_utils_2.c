/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:13:24 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/23 16:01:30 by gcatarin         ###   ########.fr       */
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

int	div_status(int status)
{
	while (status >= 256)
		status /= 256;
	return (status);
}
