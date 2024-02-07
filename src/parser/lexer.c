/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:54:09 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/07 13:12:58 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	read_words(int i, char *str, t_lex *lex_lst)
{
	int	j;

	j = 0;
	while (str[i + j] && !(check_token(str[i + j])))
	{
		if (is_quote(str[i + j]))
			str = remove_quote(str, i + j);
		if (is_whitespace(str[i + j]))
			break ;
		else
			j++;
	}
	if (!add_token(ft_substr(str, i, j), 0, lex_lst))
		return (-1);
	return (j);
}

int	handle_token(char *str, int i, t_lex *lex_lst)
{
	char	*token;

	token = check_token(str[i]);
	if (strncmp(token, "GREAT", 5))
	{
		token = check_token(str[i + 1]);
		if (strncmp(token, "GREAT", 5))
		{
			 if (!add_token("GREATGREAT", 1, lex_lst))
			 	return (-1);
			return (2);
		}
	}
	else if (strncmp(token, "LESS", 4))
	{
		token = check_token(str[i + 1]);
		if (strncmp(token, "LESS", 4))
		{
			if (!add_token("LESSLESS", 1, lex_lst))
				return (-1);
			return (2);
		}
	}
	else if (token)
	{
		if (!add_token(token, 1, lex_lst))
			return (-1);
		return (1);
	}
	return (0);
}

void	tokeniser(t_paths *p, t_lex *lex_lst)
{
	int	i;
	int	j;

	i = 0;
	if (check_token(p->args[ft_strlen(p->args) - 1]))
	{
		error_msg("Syntax Error!");
		return ;
	}
	while (p->args[i])
	{
		j = 0;
		i += skip_spaces(p->args, i);
		if (check_token(p->args[i]))
			j = handle_token(p->args, i, lex_lst);
		else
			j = read_words(i, p->args, lex_lst);
		if (j < 0)
		{
			error_msg("Failure adding node!");
			return ;
		}
		i += j;
	}
}
