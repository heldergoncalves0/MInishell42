/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:44:43 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/11 14:36:31 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_array(char **args)
{
	int		i;

void	exitcase(t_shell *p, char *s)
{
	int		i;

	i = 0;
	while (args && args[i])
	{
		free(args[i++]);
	}
	free(args);
	return (NULL);
}

t_cmd *free_cmds(t_cmd *c)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = c;
	while (c)
	{
		tmp = c->next;
		c->args = free_array (c->args);
		free(c->path);
		free(c);
		c = tmp;
	}
	return (NULL);
}

void	free_shell(t_shell *s)
{
	rl_clear_history();
	free_cmds(s->cmd);
	free_array(s->env);
	printf("exit\n");
	exit(0);
}
