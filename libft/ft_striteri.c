/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:55:46 by becaraya          #+#    #+#             */
/*   Updated: 2018/11/14 14:16:13 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int				i;
	unsigned int	count;

	i = 0;
	count = 0;
	if (!s || !f)
		return ;
	while (*s != '\0')
	{
		(f(count, s));
		count++;
		s++;
	}
}
