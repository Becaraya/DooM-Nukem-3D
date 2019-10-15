/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:46:13 by pitriche          #+#    #+#             */
/*   Updated: 2019/10/15 16:00:19 by pitriche         ###   ########.fr       */
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
	int	wall_heigth;
	int	wall_scale;
	int over_hor;
	int y;
	int yor;
	int	yormax;
	int ymax;
	int texx;
	int texymax;
	int texy;
	t_walls *wall;
	t_rc_hit *hit;

	y = -1;
	tx = al->tex[0].size_x * ray->angle / D_2PI;
	hit = ray->hits + ray->nb_hits - 1;
	while (++y < WIN_SIZEY)
		al->pix[y * WIN_SIZEX + x] = skybox(al, y, tx);

	wall_scale = 200 * D_2PI / al->fov;
	wall_size = (hit->ce_hei - hit->fl_hei) * wall_scale
		/ hit->hitdst;
	wall_heigth = (hit->ce_hei - hit->fl_hei) * UINT16_MAX;
	over_hor = (ray->hits[ray->nb_hits - 1].ce_hei - al->play.eyez)
		* wall_scale / ray->hits[ray->nb_hits - 1].hitdst;



	wall = &ray->hits[ray->nb_hits - 1].wall;
	y = (WIN_SIZEY / 2) - al->play.horizon - over_hor;
	yor = y;
	y = y < 0 ? 0 : y;
	ymax = (WIN_SIZEY / 2) - al->play.horizon - over_hor + wall_size;
	yormax = ymax;
	ymax = ymax > WIN_SIZEY ? WIN_SIZEY : ymax;
	texx = ray->hits[ray->nb_hits - 1].hit_texx *
	al->tex[wall->wall_tex].size_x /
	SDL_MAX_UINT16;
	texymax = yormax - yor;
	while (y < ymax)
	{
	//printf("((y - yor) * wall_heigth / texymax) > %u\n", (y - yor) * wall_heigth / texymax);
		texy = ((((y - yor) * wall_heigth / texymax) % TEX_REPEAT_V) * al->tex[wall->wall_tex].size_y) / TEX_REPEAT_V;
		//printf("%d ", texy);
		al->pix[y * WIN_SIZEX + x] = tex_find(al, texx, texy,
			&ray->hits[ray->nb_hits - 1].wall);
		y++;
	}

}
