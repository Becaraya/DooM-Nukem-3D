/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa_doom.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:59:33 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/17 08:54:38 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

char		grep_tenth(double n)
{
	double	tmp;

	tmp = floor(n);
	return (floor((n - tmp) * 10) + '0');
}

char		*dtoa_doom(double n)
{
	char	*tmp;
	char	tmp2[3];
	char	*result;

	result = NULL;
	if (n > INT_MAX)
		return (NULL);
	if (!(tmp = ft_itoa(n)))
		return (NULL);
	if (!(result = ft_strnew(sizeof(ft_strlen(tmp)) + 2)))
		return (NULL);
	result = ft_strcpy(result, tmp);
	free(tmp);
	ft_strcat(result, ".");
	tmp2[0] = grep_tenth(n);
	tmp2[1] = grep_tenth(n * 10);
	tmp2[2] = '\0';
	ft_strcat(result, tmp2);
	return (result);
}
