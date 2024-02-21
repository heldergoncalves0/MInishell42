/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:src/redirect/infile.c
/*   Created: 2024/02/13 17:42:06 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/20 16:20:09 by helferna         ###   ########.fr       */
=======
/*   Created: 2024/02/20 18:13:24 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/20 20:07:43 by gcatarin         ###   ########.fr       */
>>>>>>> parser:src/utils/ft_utils_2.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_outfile(int out, int cmd_out, int *fd)
{
<<<<<<< HEAD:src/redirect/infile.c
	//se nao existe, erro
	//se existe abro sem permissoes
	redir->fd = open(redir->args[1], O_RDONLY);
	if (redir->fd == -1 && ++cmd->is_error_redir)
		return (0);
	close_fd(cmd->in_file);
	cmd->in_file = redir->fd;
	return (1);
=======
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
>>>>>>> parser:src/utils/ft_utils_2.c
}
