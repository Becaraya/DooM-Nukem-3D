/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:48:09 by becaraya          #+#    #+#             */
/*   Updated: 2018/11/09 13:10:13 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int count;

	i = ft_strlen(s);
	count = 0;
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			while (count < i)
			{
				s++;
				count++;
			}
			return ((char *)s);
		}
		else
			i--;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}
