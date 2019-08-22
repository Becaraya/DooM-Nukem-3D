/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 17:20:15 by becaraya          #+#    #+#             */
/*   Updated: 2018/11/07 11:09:30 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;

	i = 0;
	while (str[i] == to_find[i] && str[i] != '\0')
		i++;
	if (to_find[i] == '\0')
		return ((char *)str);
	if (str[i] == '\0')
		return (NULL);
	return (ft_strstr(str + 1, to_find));
}
