/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:19:25 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/06 18:12:35 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	find_quote(char *s, int i, char c)
{
	int	j;
	
	j = i;
	while(s[++j])
	{
		if (s[j] == c)
			return(j);
	}		
	return(-1);
}

void	handle_quotes(char *s)
{
	int	i;
	
	i = 0;
	while(s[i])
	{
		if (s[i] == 39)
		{
			i = find_quote(s, i, 39);
			if (i == -1)
			{
				error_msg("Wrong number of quotes.\n");
				break;
			}
		}
		i++;
	}
	if (i == -1)
		return;
	i = 0;
	while(s[i])
	{
		if (s[i] == 34)
		{
			i = find_quote(s, i, 34);
			if (i == -1)
			{
				error_msg("Wrong number of double quotes.\n");
				break;
			}
		}
		i++;
	}
}

int	is_quote(char s)
{
	if (s == 34 || s == 39)
		return (1);
	return (0);
}

char	*remove_quote(char *s, int index)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * ft_strlen(s));
	while(s[i])
	{
		if(i == index)
			i++;
		else
			ret[i] = s[i];
		i++;
		j++;
	}
	free(s);
	return (ret);
}
