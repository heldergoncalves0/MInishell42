/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:21:25 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/13 17:39:09 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir(t_cmd *c, int i)
{
	if (ft_strncmp(c->args[i], ">", 2) == 0)
		return (1);
	else if (ft_strncmp(c->args[i], "<", 2) == 0)
		return (1);
	else if (ft_strncmp(c->args[i], ">>", 3) == 0)
		return (1);
	else if (ft_strncmp(c->args[i], "<<", 3) == 0)
		return (1);
	return (0);
}
static t_redir	*redir_struct(char *name, char *file, t_redir_type type)
{
	t_redir*redir_ptr;

	redir_ptr = ft_calloc(sizeof(t_redir), 1);
	redir_ptr->args[0] = name;
	redir_ptr->args[1] = file;
	redir_ptr->type = type;
	return (redir_ptr);
}

t_redir*redir_compares(char **args)
{
	int i;

	i = 0;
	if (ft_strncmp(args[0], ">", 2) == 0)
		return(redir_struct(args[0], args[1], OUTFILE));
	else if (ft_strncmp(args[0], "<", 2) == 0)
		return(redir_struct(args[0], args[1], INFILE));
	else if (ft_strncmp(args[0], "<<", 3) == 0)
		return(redir_struct(args[0], args[1], HEREDOC));
	else if (ft_strncmp(args[0], ">>", 3) == 0)
		return(redir_struct(args[0], args[1], APPEND));
	return (NULL);
}

void clean_redir_cmd(t_cmd *c)
{
	size_t		i;
	size_t		j;
	int			flag;

	j = 0;
	i = -1;
	flag = 0;
	while (c->args[++i])
	{
		flag = is_redir(c, i);
		if (flag)
		{	
			j = i;
			c->args[i] = 0;
			i++;
			while (c->args[++i])
			{	c->args[j++] = c->args[i];
				c->args[i] = 0;
			}
			c->args[j] = 0;
			clean_redir_cmd(c);
			break ;
		}
	}
}

void	split_redirect(t_shell *s)
{
	t_redir	*redir;
	t_redir	*end;
	t_cmd	*cmd;
	int		i;

	end = NULL;
	cmd = s->cmd;
	while (cmd)
	{
		i = 0;
		while (cmd->args[i])
		{
			redir = redir_compares(&cmd->args[i]);
			if (redir)
			{
				if (!cmd->red)
					cmd->red = redir;
				else if (end)
					end->next = redir;
				end = redir;
				i += (*cmd->args[i + 1] != '\0');
			}
			i++;
		
		}
		clean_redir_cmd(cmd);
		cmd = cmd->next;
	}
}

void	execute_redirects(t_cmd *cmd)
{
	t_redir	*redir;

	while (cmd)
	{	
		redir = cmd->red;
		while (redir)
		{
			if (redir->type == APPEND)
				printf("APPEND\n");
			if (redir->type == INFILE)
				handle_infile(cmd, redir);
			if (redir->type == OUTFILE)
				printf("OUTFILE\n");
			if (redir->type == HEREDOC)
				handle_heredoc(cmd, redir);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}