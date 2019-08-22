/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 15:07:43 by becaraya          #+#    #+#             */
/*   Updated: 2018/11/17 15:07:53 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_power(int nb, int power)
{
	int result;

	result = 1;
	if (power == 0)
		return (1);
	if (power < 0 || nb == 0)
		return (0);
	if (power > 1)
		result = ft_power(nb, power - 1);
	return (result * nb);
}
