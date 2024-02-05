/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:09:52 by helferna          #+#    #+#             */
/*   Updated: 2022/11/01 15:12:31 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *saco, const char *bola, size_t len)
{
	size_t	i;
	size_t	j;

	if (bola[0] == '\0' || bola == NULL)
		return ((char *)saco);
	if (len == 0)
		return (NULL);
	i = 0;
	while (saco[i] != '\0')
	{
		j = 0;
		while (saco[i + j] == bola[j] && (i + j) < len)
		{
			if (saco[i + j] == '\0' && bola[j] == '\0')
				return ((char *)&saco[i]);
			j++;
		}
		if (bola[j] == '\0')
			return ((char *)saco + i);
		i++;
	}
	return (0);
}

/*int 	main(int ac, char **av)
{
	char *s1 = av[1];
	char *s2 = av[2];

	if (ac == 3)
	{
		s1 = ft_strnstr(s1, s2, 3);
		printf("%s\n", s2);
	}
	return (0);
}*/