/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:27:22 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/15 18:59:06 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc_read(t_redir *redir)
{
	char	*line;
	size_t	size;

	size = ft_strlen(redir->args[1]) + 1;
	while (1)
	{
		line = readline(">> ");
		if (line == EOF)
			ft_putstr_fd("\n\nDEU MERDA\n\n", 2);
		if (!line || ft_strncmp(line, redir->args[1], size) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, redir->fd);
		ft_putstr_fd("\n", redir->fd);
		free(line);
	}
}

void	handle_heredoc(t_shell *s, t_cmd *cmd, t_redir *redir)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		s->status = 0;
		redir->fd = open("/tmp/tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (redir->fd == -1)
		{
			s->status = -1;// corrigir se -1
			free_shell(s);
		}
		handle_heredoc_read(redir);
		close_fd(redir->fd);
		free_shell(s);
	}
	wait(NULL);
	redir->fd = open("/tmp/tmp.txt", O_RDONLY);
	if (redir->fd == -1)
		cmd->is_error_redir = 1;
	close_fd(cmd->in_file);
	cmd->in_file = redir->fd;
}
