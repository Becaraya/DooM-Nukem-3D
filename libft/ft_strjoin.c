/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:10:00 by becaraya          #+#    #+#             */
/*   Updated: 2019/11/06 15:17:20 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinend(char const *s1, char const *s2)
{
	char	*r;

	if (s1 && s2)
	{
		if (!(r = (char *)malloc(sizeof(char) * (ft_strlen(s1)
			+ ft_strlen(s2) + 1))))
			return (NULL);
		ft_strcpy(r, s1);
		ft_strcat(r, s2);
		r[ft_strlen(s1) + ft_strlen(s2) + 1] = '\0';
		return (r);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;

	if (s1 && s2)
	{
		if (!(r = (char *)malloc(sizeof(char) * (ft_strlen(s1)
			+ ft_strlen(s2) + 1))))
			return (NULL);
		ft_strcpy(r, s1);
		ft_strcat(r, s2);
		return (r);
	}
	return (NULL);
}
