/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:45:10 by becaraya          #+#    #+#             */
/*   Updated: 2019/03/07 15:54:22 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

char	*ft_strdup(const char *s)
{
	int		len;
	int		count;
	char	*result;

	count = 0;
	len = ft_strlen(s);
	if (!(result = (char *)malloc(sizeof(char) * len + 1)) || !(s))
		return (NULL);
	while (count < len)
	{
		result[count] = s[count];
		count++;
	}
	result[count] = '\0';
	return (result);
}
