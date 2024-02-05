/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:08:10 by helferna          #+#    #+#             */
/*   Updated: 2022/11/01 21:42:02 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_strtrim(char const *s1, char const *set)
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
