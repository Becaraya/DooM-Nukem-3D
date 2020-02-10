/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_f.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:40:36 by becaraya          #+#    #+#             */
/*   Updated: 2020/02/06 15:26:36 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** free the first pointer
*/

char	*ft_strjoinfreef(char *s1, char const *s2)
{
	char	*r;

	if (s1 && s2)
	{
		if (!(r = (char *)malloc(sizeof(char) * (ft_strlen(s1)
			+ ft_strlen(s2) + 1))))
			return (NULL);
		ft_strcpy(r, s1);
		ft_strdel(&s1);
		ft_strcat(r, s2);
		return (r);
	}
	return (NULL);
}
