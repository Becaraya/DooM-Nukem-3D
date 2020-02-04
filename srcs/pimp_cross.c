/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pimp_cross.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:45:55 by pitriche          #+#    #+#             */
/*   Updated: 2020/02/04 16:29:24 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		pimp_cross(t_al *al)
{
	int		i;

	i = WIN_SIZEY / 2 - 12;
	while (i <= WIN_SIZEY / 2 + 12)
	{
		while (i < WIN_SIZEY / 2 + 2 && i > WIN_SIZEY / 2 - 2)
			i++;
		al->pix[i * WIN_SIZEX + WIN_SIZEX / 2 - 1] = 0x000000;
		al->pix[i * WIN_SIZEX + WIN_SIZEX / 2] = 0x52fc03;
		al->pix[i * WIN_SIZEX + WIN_SIZEX / 2 + 1] = 0x000000;
		i++;
	}
	i = WIN_SIZEX / 2 - 12;
	while (i <= WIN_SIZEX / 2 + 12)
	{
		while (i < WIN_SIZEX / 2 + 2 && i > WIN_SIZEX / 2 - 2)
			i++;
		al->pix[WIN_SIZEX * (WIN_SIZEY / 2 - 1) + i] = 0x0000000;
		al->pix[WIN_SIZEX * WIN_SIZEY / 2 + i] = 0x52fc03;
		al->pix[WIN_SIZEX * (WIN_SIZEY / 2 + 1) + i] = 0x0000000;
		i++;
	}
}
/*
**void		invert_pix(unsigned int *pix)
**{
**	*pix = 0x52fc03;
**	// if (((*pix >> 16) & 0xff) < 108 && 148 > ((*pix >> 16) & 0xff) &&
**	// ((*pix > 8) & 0xff) < 108 && 148 > ((*pix > 8) & 0xff) &&
**	// (*pix & 0xff) && (*pix & 0xff))
**	// 	{
**	// 		*pix = 0xFFFFFF;
**	// 	}
**	// *pix = ~(*pix);
**}
*/
