/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 01:45:57 by pitriche          #+#    #+#             */
/*   Updated: 2019/12/12 03:44:44 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

inline int	skybox(t_al *al, int y, int tx)
{
	int ty;

	ty = al->tex[0].size_y * (y + al->play.horizon + HORIZON_LIMIT)
	/ al->stretch;
	return (al->tex[0].pix[ty * al->tex[0].size_x + tx]);
}

inline int	tex_find(unsigned int *pix, int texx, int texy, t_tex *tex)
{
	int color;

	if ((color = tex->pix[tex->size_x * texy + texx]) >> 24)
		*pix = color;
	else
		return (1);
	return (0);
}

inline void	cap_int(int *var, int lowcap, int highcap)
{
	if (*var < lowcap)
		*var = lowcap;
	if (*var > highcap)
		*var = highcap;
}
