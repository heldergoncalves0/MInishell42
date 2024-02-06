/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:21:50 by gcatarin          #+#    #+#             */
/*   Updated: 2024/02/06 16:26:44 by gcatarin         ###   ########.fr       */
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

static int	c_set(char c, char *set)
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

char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	int		a;
	int		z;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	a = 0;
	while (s1[a] && c_set(s1[a], set))
		a++;
	z = ft_strlen(s1);
	while (z > a && c_set(s1[z - 1], set))
		z--;
	dest = (char *)malloc(sizeof(char) * z - a + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i] && a < z)
	{
		dest[i] = s1[a];
		i++;
		a++;
	}
	dest[i] = '\0';
	return (dest);
}