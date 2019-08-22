/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 17:36:21 by becaraya          #+#    #+#             */
/*   Updated: 2018/11/14 13:34:15 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_result(char *result, long int nbr, int n)
{
	if (n < 0)
		result[1] = nbr + '0';
	else
		result[0] = nbr + '0';
	return (result);
}

static int		ft_len(int n)
{
	long int		nbr;
	int				i;

	nbr = n;
	i = 0;
	if (nbr < 0)
		nbr = nbr * -1;
	while (nbr / 10 > 9)
	{
		i++;
		nbr = nbr / 10;
	}
	if (n < 0)
		return (i + 2);
	else
		return (i + 1);
}

char			*ft_itoa(int n)
{
	long int		nbr;
	int				neg;
	int				i;
	char			*result;

	nbr = n;
	neg = 0;
	i = 0;
	neg = (nbr < 0) ? -1 : 0;
	if (!(result = (char *)malloc(sizeof(char) * ft_len(n) + 1 - neg)))
		return (NULL);
	if (nbr < 0)
	{
		nbr = nbr * -1;
		result[i] = '-';
		i++;
	}
	while ((ft_len(n) - i) > 0 && n != 0 && nbr > 9)
	{
		result[ft_len(n) - i - neg] = (nbr % 10) + '0';
		nbr = nbr / 10;
		i++;
	}
	result[ft_len(n) + 1] = '\0';
	return (ft_result(result, nbr, n));
}
