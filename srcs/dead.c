/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 09:13:43 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/21 10:36:12 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	pix_to_pix(unsigned *src, unsigned *dst)
{
	unsigned i;

	i = 0;
	while (i < WIN_SIZEX * WIN_SIZEY)
	{
		dst[i] = src[i];
		i++;
	}
}

void	dead(t_al *al)
{
	pix_to_pix(al->pix_dead, al->pix);
}
