/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:08:21 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/18 16:52:08 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*delete_quotes(char *arg, char c)
{
	size_t	i;
	size_t	j;
	char	*ret;
	
	ret = calloc(1, ft_strlen(arg));
	i = 0;
	j = 0;
	while (arg[j])
	{
		while (arg[j] == c)
			j++;
		if (arg[j])
			ret[i++] = arg[j++];
	}
	free(arg);
	return (ret);
}

static char	*trim_quotes(char *arg, char c)
{
	size_t	i;
	size_t	j;
	char *ret;

	i = 0;
	j = 1;
	ret = calloc(1, ft_strlen(arg));
	arg = delete_quotes(arg, c);
	if (arg[0] == c)
	{
		while (arg[j] != c)
			ret[i++] = arg[j++];
		ret[i + 1] = '\0';
		free(arg);
		return (ret);
	}
	free(ret);
	return (arg);
}

void	handle_quotes(t_shell *s)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = s->cmd;
	while (cmd)
	{
		i = 0;
		while (cmd->args[i])
		{
			if (cmd->args[i][0] == 34)
				cmd->args[i] = trim_quotes(cmd->args[i], '\"');
			if (cmd->args[i][0] == 39)
				cmd->args[i] = trim_quotes(cmd->args[i], '\'');
			i++;
		}
		cmd = cmd->next;
	}
}
