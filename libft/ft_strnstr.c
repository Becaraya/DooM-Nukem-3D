/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:26:07 by becaraya          #+#    #+#             */
/*   Updated: 2018/11/15 18:41:56 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t i;

	i = 0;
	while (str[i] == to_find[i] && str[i] != '\0' && (i < len))
		i++;
	if (to_find[i] == '\0')
		return ((char *)str);
	if (str[i] == '\0' || len == i)
		return (NULL);
	return (ft_strnstr(str + 1, to_find, (len - 1)));
}
