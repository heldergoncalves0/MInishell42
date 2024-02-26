/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:13:24 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/26 13:58:07 by gcatarin         ###   ########.fr       */
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

int	change_infile(int in, int cmd_in)
{
	if (cmd_in != -1)
	{
		close_fd(in);
		return (cmd_in);
	}
	return (in);
}

void	clean_null_expansion(t_shell *s)
{
	size_t	i;
	t_cmd	*cmd;
	size_t	j;

	i = 0;
	cmd = s->cmd;
	while (cmd)
	{
		while (cmd->args[i] && ft_strlen(cmd->args[i]) == 0)
		{
			j = i;
			cmd->args[i] = 0;
			while (cmd->args[++i])
			{
				cmd->args[j++] = cmd->args[i];
				cmd->args[i] = 0;
			}
			cmd->args[j] = 0;
			clean_null_expansion(s);
			break ;
		}
		cmd = cmd->next;
	}
}

t_shell	*terminal(void)
{
	static t_shell	shell;

	return (&shell);
}

void	dir_error(char *s)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_ln(": Is a directory", 2);
}
