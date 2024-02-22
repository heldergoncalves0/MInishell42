/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:03:03 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/22 18:15:50 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_cmd *c, int i)
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

int	is_arg_redir(char *s)
{
	if (ft_strncmp(s, ">", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(s, ">>", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "<<", 3) == 0)
		return (1);
	return (0);
}

int	sintax_verify(t_shell *shell)
{
	size_t	i;
	t_cmd	*cmd;

	i = 0;
	cmd = shell->cmd;
	while (cmd)
	{
		i = -1;
		while (cmd->args[++i])
		{
			if (is_arg_redir(cmd->args[i]) == 1)
			{
				if (cmd->args[i + 1])
				{
					if (is_arg_redir(cmd->args[i + 1]) == 1)
						return (ft_putstr_ln("Syntax Error!", 2));
				}
				else
					return (ft_putstr_ln("Syntax Error!", 2));
			}
		}
		cmd = cmd->next;
	}
	return (0);
}

int	ft_ismorealnum(int str)
{
	if ((str >= 97 && str <= 122) || \
	(str >= 65 && str <= 90))
		return (1);
	else if (str >= 48 && str <= 57)
		return (1);
	else if (str == '?')
		return (1);
	return (0);
}

char	*ft_strchr_quotes(char *s, int c)
{
	int		flag;
	size_t	i;

	flag = 0;
	i = 1;
	while (*s)
	{
		if (*s == 34 && flag == 0)
			flag = 1;
		else if (*s == 39 && flag == 0)
			flag = 2;
		else if (*s == 34 && flag == 1)
			flag = 0;
		else if (*s == 39 && flag == 2)
			flag = 0;
		else if ((unsigned char)c == *s && flag < 2 && ft_ismorealnum(s[i]) == 1)
			return ((char *)s);
		s++;
	}
	return (0);
}

int	ft_strint_quotes(char *s, int c)
{
	int		flag;
	size_t	i;
	size_t	counter;

	flag = 0;
	i = 1;
	counter = 1;
	while (*s)
	{
		if (*s == 34 && flag == 0)
			flag = 1;
		else if (*s == 39 && flag == 0)
			flag = 2;
		else if (*s == 34 && flag == 1)
			flag = 0;
		else if (*s == 39 && flag == 2)
			flag = 0;
		else if ((unsigned char)c == *s && flag < 2 && ft_ismorealnum(s[i]) == 1)
			return (counter);
		s++;
		counter++;
	}
	return (0);
}

int	ft_isquoted(char c, int flag)
{
	if (flag == 0)
	{
		if (c == '\"')
			return (1);
		else if (c == '\'')
			return (2);
		return (0);
	}
	if (flag == 1)
	{
		if (c == '\"')
			return (0);
		return (1);
	}
	if (flag == 2)
	{
		if (c == '\'')
			return (0);
		return (2);
	}
	return (0);
}
