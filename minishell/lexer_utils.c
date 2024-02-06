/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:11:57 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/06 17:42:26 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char s)
{
	if (s == ' ' || (s > 8 && s < 14))
		return (1);
	return (0);
}

int	skip_spaces(char *s, int i)
{
	int j;

	j = 0;
	if (s[i] == ' ' || (s[i] > 8 && s[i] < 14))
	{
		j++;
		i++;
	}
	return(j);
}

char	*check_token(int c)
{
	if (c == '|')
		return ("PIPE");
	if (c == '>')
		return ("GREAT");
	if (c == '<')
		return ("LESS");
	return (0);
}
