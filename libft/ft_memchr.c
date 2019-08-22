/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 12:50:25 by becaraya          #+#    #+#             */
/*   Updated: 2018/11/13 15:33:50 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t count;

	count = 0;
	while (count < n)
	{
		if (((unsigned char *)s)[0] == (unsigned char)c)
			return ((void *)s);
		s++;
		count++;
	}
	return (NULL);
}
