/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:21:54 by becaraya          #+#    #+#             */
/*   Updated: 2018/11/12 12:05:06 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			count;
	unsigned char	*dest_;
	unsigned char	*src_;

	count = 0;
	dest_ = (unsigned char *)dest;
	src_ = (unsigned char *)src;
	while (count < n)
	{
		dest_[count] = src_[count];
		if (src_[count] == (unsigned char)c)
			return (dest + 1 + count);
		count++;
	}
	return (NULL);
}
