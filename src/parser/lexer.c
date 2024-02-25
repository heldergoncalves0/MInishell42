/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:54:09 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/25 10:26:20 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*line_treat(char *str, char *new, size_t *index)
{
	size_t	i;
	size_t	j;

	i = (str[0] == '>' || str[0] == '<' || str[0] == '|');
	i += (i && (str[1] == '>' || str[1] == '<'));
	if (i)
	{
		j = *index;
		new[j++] = '\2';
		if (str[0] == '|')
			str[0] = '\3';
		new[j++] = str[0];
		if (i == 2)
			new[j++] = str[1];
		new[j++] = '\2';
		index[0] = j;
	}
	return (str + i);
}

static char	*line_dup(char *str, char *new)
{
	char	flag;
	size_t	i;
	size_t	j;

	flag = 0;
	i = 0;
	while (*str)
	{
		j = i;
		if (*str == flag)
			flag = 0;
		else if (flag == 0 && (*str == '\'' || *str == '\"'))
			flag = *str;
		if (!flag && ft_isspace(*str))
			*str = '\2';
		else if (flag == 0)
			str = line_treat(str, new, &i);
		if (j != i)
			continue ;
		new[i++] = *str;
		str++;
	}
	return (flag_return(flag, new));
}

static t_cmd	*new_cmd(char **args)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (cmd == NULL)
		return (NULL);
	cmd->args = args;
	cmd->fd[0] = 0;
	cmd->fd[1] = 1;
	cmd->in_file = -1;
	cmd->out_file = -1;
	cmd->pid = 0;
	cmd->path = NULL;
	return (cmd);
}

static int	cmd_loop(char *tokens, t_shell *s, int valid)
{
	char	**cmds;
	size_t	i;
	t_cmd	*end;
	t_cmd	*cmd;

	cmds = ft_split(tokens, '\3', 0);
	s->cmd = NULL;
	end = NULL;
	i = -1;
	while (cmds[++i])
	{
		if (ft_strncmp(cmds[i], "\2", 2) == 0 || cmds[i] == NULL)
			valid = 0;
		cmd = new_cmd(ft_split(cmds[i], '\2', 0));
		s->num_cmds++;
		if (!s->cmd)
			s->cmd = cmd;
		else if (end)
			end->next = cmd;
		end = cmd;
	}
	free_array(cmds);
	return (valid);
}

int	tokeniser(const char *str, t_shell *s)
{
	char	*tokens;
	int		valid;

	valid = 0;
	tokens = line_dup((char *) str, ft_calloc(10, ft_strlen(str)));
	if (tokens == NULL)
		ft_putstr_fd("Syntax error\n", 2);
	else
	{
		if (cmd_loop(tokens, s, 1) == 0)
		{
			ft_putstr_fd("Syntax Error !\n", 2);
			valid = 1;
		}
	}
	free(tokens);
	return (valid);
}
