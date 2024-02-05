/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:47:52 by helferna          #+#    #+#             */
/*   Updated: 2023/03/13 16:33:10 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (read(fd, 0, 0) < 0 || BUFFER_SIZE < 1)
	{
		ft_bzero(buffer, BUFFER_SIZE);
		return (NULL);
	}
	line = NULL;
	while (buffer[0] || read(fd, buffer, BUFFER_SIZE))
	{
		line = ft_strjoin_gnl(line, buffer);
		if (adjust_buffer_after_newline(buffer))
			break ;
	}
	return (line);
}
/*
int main()
{
	int i = 8;
	char	*line;
	int		fd = open("teste", O_RDWR);
	while (1)
	{
		if (!line)
			break;
		line = get_next_line(fd);
		printf("%s", line);
	}
	return (0);
}
*/