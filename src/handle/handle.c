/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 18:27:22 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/13 11:08:58 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_shell *s, int pipe)
{/*
	char 	*tmp;
	char	*hered;
	char 	*line;

	hered = ft_calloc(1, sizeof(char));
	while (1)
	{
		line = readline(">");
		if (index)
		if (ft_strncmp(line, arr[index], 3) == 0)
		{
			index++;
			ft_putstr_fd(hered,	pipe);
			free(hered);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		hered = ft_strjoin(hered, tmp);
		free(tmp);
		free(line);
	}
	return ();*/
}

char *handle_redir_out(t_shell *s)
{
	char	*outfile;
	int		i;

	i = 0;
	while (s->cmd->args[i])
	{
		if (ft_strncmp(s->cmd->args[i], ">", 2) == 0)
		{
			outfile = s->cmd->args[++i];
			s->cmd->args[i] = NULL;
			s->cmd->args[i - 1] = NULL;
			open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
		}
		i++;
	}
	return (outfile);
}
