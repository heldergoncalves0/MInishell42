/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:09:49 by helferna          #+#    #+#             */
/*   Updated: 2023/03/13 16:32:43 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t len)
{
	ft_memset(s, 0, len);
}

void	*ft_memset(char *dest, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)dest)[i] = c;
		i++;
	}
	return (dest);
}

size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new_str = malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (!new_str)
		return (NULL);
	if (s1)
	{
		while (s1[i] != '\0')
			new_str[j++] = s1[i++];
	}
	free(s1);
	i = 0;
	while (s2[i])
	{
		new_str[j++] = s2[i];
		if (s2[i++] == '\n')
			break ;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	adjust_buffer_after_newline(char *buff)
{
	int	i;
	int	toggle;
	int	j;

	i = 0;
	j = 0;
	toggle = 0;
	while (buff[i])
	{
		if (toggle)
			buff[j++] = buff[i];
		if (buff[i] == '\n')
			toggle = 1;
		buff[i++] = '\0';
	}
	return (toggle);
}
