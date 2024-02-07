/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:17:39 by helferna          #+#    #+#             */
/*   Updated: 2022/11/03 12:42:18 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	size_t	i;

	if (dest == src)
		return (dest);
	i = 0;
	if (src < dest)
	{
		i = count;
		while (i > 0)
		{
			i--;
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		}
	}
	else
		ft_memcpy((unsigned char *)dest, (unsigned char *)src, count);
	return (dest);
}

/*int main( void )
{
  char dest [50];
  char src[] = "Source to be moved";
}*/