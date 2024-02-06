/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:21:50 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/06 13:30:09 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char *s, size_t start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (start >= ft_strlen(s))
		new_str = malloc(1);
	else if (len >= ft_strlen(s))
		new_str = (char *)malloc(ft_strlen(s) - start + 1);
	else
		new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	i = start;
	j = 0;
	while (i <= ft_strlen(s) && j < len)
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	return (new_str);
}

size_t ft_strlen(char *s)
{
	size_t i;
	
	i = 0;
	while(s[i])
		i++;
	return(i);
}