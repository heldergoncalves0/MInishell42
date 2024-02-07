/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:31:43 by helferna          #+#    #+#             */
/*   Updated: 2022/11/04 13:37:07 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
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
