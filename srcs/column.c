/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:46:13 by pitriche          #+#    #+#             */
/*   Updated: 2019/10/15 13:24:27 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

inline int	skybox(t_al *al, int y, int tx)
{
	int ty;

	ty = al->tex[0].size_y * (y + al->play.horizon + HORIZON_LIMIT)
	/ al->stretch;
	return (al->tex[0].pix[ty * al->tex[0].size_x + tx]);
}

inline int	tex_find(t_al *al, int texx, int texy, t_walls *wall)
{
	return (al->tex[wall->wall_tex].pix[al->tex[wall->wall_tex].size_x * texy +
		texx]);
}

void		column(t_al *al, int x, t_rc_ray *ray)
{
	int tx;
	int	wall_size;
	int	wall_scale;
	int over_hor;
	int y;
	int yor;
	int	yormax;
	int ymax;

	y = -1;
	tx = al->tex[0].size_x * ray->angle / D_2PI;
	while (++y < WIN_SIZEY)
		al->pix[y * WIN_SIZEX + x] = skybox(al, y, tx);

	wall_scale = 180 * D_2PI / al->fov;
	wall_size = (ray->hits[ray->nb_hits - 1].ce_hei
		- ray->hits[ray->nb_hits - 1].fl_hei) * wall_scale
		/ ray->hits[ray->nb_hits - 1].hitdst;

	over_hor = (ray->hits[ray->nb_hits - 1].ce_hei - al->play.eyez)
		* wall_scale / ray->hits[ray->nb_hits - 1].hitdst;



	y = (WIN_SIZEY / 2) - al->play.horizon - over_hor;
	yor = y;
	y = y < 0 ? 0 : y;
	ymax = (WIN_SIZEY / 2) - al->play.horizon - over_hor + wall_size;
	yormax = ymax;
	ymax = ymax > WIN_SIZEY ? WIN_SIZEY : ymax;
	//printf("%u - ", ray->hits[ray->nb_hits - 1].hit_texx);
	int texx = ray->hits[ray->nb_hits - 1].hit_texx * al->tex[ray->hits[ray->nb_hits - 1].wall.wall_tex].size_x / SDL_MAX_UINT16;
	int texymax = yormax - yor;
	int texy;
	//printf("%u - ", texx);
	while (y < ymax)
	{
		texy = (y - yor) * al->tex[ray->hits[ray->nb_hits - 1].wall.wall_tex].size_x / texymax;
		//printf("%d ", texy);
		al->pix[y * WIN_SIZEX + x] = tex_find(al, texx, texy,
			&ray->hits[ray->nb_hits - 1].wall);
		y++;
	}

}
