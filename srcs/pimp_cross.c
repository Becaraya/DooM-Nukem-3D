/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pimp_cross.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:45:55 by pitriche          #+#    #+#             */
/*   Updated: 2019/12/12 03:44:44 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		invert_pix(unsigned int *pix)
{
	*pix = ~(*pix);
}

void		pimp_cross(t_al *al)
{
	int i;

	i = WIN_SIZEY / 2 - 12;
	while (i <= WIN_SIZEY / 2 + 12)
	{
		invert_pix(al->pix + i * WIN_SIZEX + WIN_SIZEX / 2 - 1);
		invert_pix(al->pix + i * WIN_SIZEX + WIN_SIZEX / 2);
		invert_pix(al->pix + i * WIN_SIZEX + WIN_SIZEX / 2 + 1);
		i++;
	}
	i = WIN_SIZEX / 2 - 12;
	while (i <= WIN_SIZEX / 2 + 12)
	{
		if (i < WIN_SIZEX / 2 - 1 || i > WIN_SIZEX / 2 + 1)
		{
			invert_pix(al->pix + WIN_SIZEX * (WIN_SIZEY / 2 - 1) + i);
			invert_pix(al->pix + WIN_SIZEX * WIN_SIZEY / 2 + i);
			invert_pix(al->pix + WIN_SIZEX * (WIN_SIZEY / 2 + 1) + i);
		}
		i++;
	}
}
