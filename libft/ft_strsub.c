/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:51:36 by becaraya          #+#    #+#             */
/*   Updated: 2018/11/14 11:29:44 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	count;
	char	*result;

	count = 0;
	if (!(result = ft_strnew(len)) || !s)
		return (NULL);
	while (count++ < start)
		s++;
	result = ft_strncpy(result, s, len);
	return (result);
}
