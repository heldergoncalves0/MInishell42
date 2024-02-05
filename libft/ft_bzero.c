/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:37:16 by helferna          #+#    #+#             */
/*   Updated: 2022/10/28 16:57:16 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

void	ft_bzero(void *s, size_t len)
{
	ft_memset(s, 0, len);
}

/*int main(void)
{
	char *string;
	char sa[21];

	ft_bzero(sa, sizeof(sa));
	string = (char *)memset(sa, 'A', 10);
	printf("\n%s\n", string);
}*/