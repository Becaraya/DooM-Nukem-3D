/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 14:45:13 by becaraya          #+#    #+#             */
/*   Updated: 2018/11/13 10:45:47 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	count;

	count = 0;
	if (dest > src)
	{
		while (count < n)
		{
			((unsigned char*)dest)[n - 1] = ((unsigned char*)src)[n - 1];
			n--;
		}
	}
	else
	{
		while (count < n)
		{
			((unsigned char*)dest)[count] = ((unsigned char*)src)[count];
			count++;
		}
	}
	return ((unsigned char *)dest);
}
