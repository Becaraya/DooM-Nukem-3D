/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:39:49 by becaraya          #+#    #+#             */
/*   Updated: 2018/11/09 11:22:11 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp;
	size_t			count;

	tmp = (unsigned char *)s;
	count = 0;
	while (count < n)
	{
		tmp[count] = (unsigned char)c;
		count++;
	}
	return (s);
}
