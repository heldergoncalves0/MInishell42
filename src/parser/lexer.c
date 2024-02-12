/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:54:09 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/12 13:07:08 by helferna         ###   ########.fr       */
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
			continue;
		new[i++] = *str;
		str++;
	}
	if (flag == 0)
		return (new);
	free(new);
	return (NULL);
}

t_cmd	*new_cmd(char **args, int index)
{
	t_cmd	*cmd;
	size_t	j;
	
	j = 0;
	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (cmd == NULL)
		return (NULL);
	cmd->index  = index;
	cmd->args = args;
	return (cmd);
}

void	cmd_loop(char *tokens, t_shell *s)
{
	char	**cmds;
	size_t	i;
	t_cmd	*end;
	t_cmd	*cmd;

	cmds = ft_split(tokens, '\3');
	s->cmd = NULL;
	end = NULL;
	i = 0;
	while (cmds[i])
	{
		cmd = new_cmd(ft_split(cmds[i], '\2'), i + 1);
		if (cmd == NULL)
			break;
		if (!s->cmd)
			s->cmd = cmd;
		else if (end)
			end->next = cmd;
		end = cmd;
		i++;
	}
	free_array(cmds);
}

void	tokeniser(const char *str, t_shell *s)
{
	char	*tokens;
	int		j;

	j = 0 ;
	tokens = line_dup((char *) str, ft_calloc(10, ft_strlen(str)));
	if (tokens != NULL)
		cmd_loop(tokens, s);
	else
		write(2, "Syntax Error!\n", 14);
	free(tokens);
}
