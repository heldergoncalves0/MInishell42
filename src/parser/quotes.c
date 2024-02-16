/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:34:20 by helferna          #+#    #+#             */
/*   Updated: 2024/02/16 14:56:02 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	c_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	get_something(char *str)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	j = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			flag = 1;
			i++;
		}
		while (str[i] && flag)
		{
			if (str[i] == '\"')
				flag = 0;
			j++;
			i++;
		}
		if (!flag)
			i++;
		j++;
	}
	ft_putstr_fd("Len: ", 2);
	ft_putendl_fd(ft_itoa(j), 2);
	return (j);
}

static char *trim_quotes(char *arg)
{
	char	*trimmed;
	int		len;
	int		i;
	trimmed = NULL;
	
	len = get_something(arg);
	trimmed = calloc(len + 1, sizeof(char));
	i = 0;
	len = 0;
	while (arg[i])
	{
		if (arg[i] == '\"')
        {
            i++;
            while (arg[i])
            {
                if (arg[i] == '\"')
                {
                    i++;
                    break;
                }
                trimmed[len++] = arg[i++];
            }
        }
        else
            trimmed[len++] = arg[i++];
	}
	trimmed[len] = '\0';
	return (trimmed);
}

void	handle_quotes(t_shell *s)
{
	int		i;
	t_cmd	*cmd;
	char	*arg;

	i = 0;
	cmd = s->cmd;
	while (cmd)
	{
		i = 0;
		while (s->cmd->args[i])
		{
			// ft_putstr_fd(s->cmd->args[i], 2);
			// ft_putstr_fd("\n", 2);
			arg = ft_strdup(s->cmd->args[i]);
			free(cmd->args[i]);
			cmd->args[i] = trim_quotes(arg);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("\n", 2);
			i++;
		}
		cmd = cmd->next;
	}
}
