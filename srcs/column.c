/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:46:13 by pitriche          #+#    #+#             */
/*   Updated: 2019/10/16 12:57:06 by pitriche         ###   ########.fr       */
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

inline int	tex_find(t_al *al, int texx, int texy, t_tex *tex)
{
	return (tex->pix[tex->size_x * texy + texx]);
}

void		column_wall(t_al *al, int x, int wall_size, int over_hor,
	int wall_heigth, int texx, t_tex *tex)
{
	int y;
	int yor;
	int	yormax;
	int ymax;
	int texymax;
	int texy;

	y = (WIN_SIZEY / 2) - al->play.horizon - over_hor;
	yor = y;
	y = y < 0 ? 0 : y;
	ymax = (WIN_SIZEY / 2) - al->play.horizon - over_hor + wall_size;
	yormax = ymax;
	ymax = ymax > WIN_SIZEY ? WIN_SIZEY : ymax;
	texymax = yormax - yor;
	while (y < ymax)
	{
	//printf("((y - yor) * wall_heigth / texymax) > %u\n", (y - yor) * wall_heigth / texymax);
		texy = ((((y - yor) * wall_heigth / texymax) % TEX_REPEAT_V) *
			tex->size_y) / TEX_REPEAT_V;
		al->pix[y * WIN_SIZEX + x] = tex_find(al, texx, texy, tex);
		y++;
	}
}

void		column(t_al *al, int x, t_rc_ray *ray)
{
	int cur_hit;
	int tx;
	int y;
	int	wall_size;
	int	wall_height;
	int	wall_scale;
	int over_hor;
	int texx;
	t_tex		*tex;
	t_rc_hit	*hit;

	tx = al->tex[0].size_x * ray->angle / D_2PI;
	y = -1;
	while (++y < WIN_SIZEY)
		al->pix[y * WIN_SIZEX + x] = skybox(al, y, tx);
	wall_scale = 200 * D_2PI / al->fov;

	cur_hit = 0;
	while (cur_hit < ray->nb_hits - 1)
	{
		hit = ray->hits + cur_hit;
		// top walls
		if ((wall_height = (hit->ce_hei - ray->hits[cur_hit + 1].ce_hei) *
				UINT16_MAX) > 0)
		{
			wall_size = (hit->ce_hei - ray->hits[cur_hit + 1].ce_hei) *
				wall_scale / hit->hitdst;
			over_hor = (hit->ce_hei - al->play.eyez)
				* wall_scale / hit->hitdst;
			tex = al->tex + hit->wall.top_tex;
			texx = hit->hit_texx * tex->size_x / SDL_MAX_UINT16;
			column_wall(al, x, wall_size, over_hor, wall_height, texx, tex);
		}
		// bottom walls
		if ((wall_height = (ray->hits[cur_hit + 1].fl_hei - hit->fl_hei) *
				UINT16_MAX) > 0)
		{
			wall_size = (ray->hits[cur_hit + 1].fl_hei - hit->fl_hei) *
				wall_scale / hit->hitdst;
			over_hor = (hit->fl_hei - al->play.eyez)
				* wall_scale / hit->hitdst + wall_size;
			tex = al->tex + hit->wall.bot_tex;
			texx = hit->hit_texx * tex->size_x / SDL_MAX_UINT16;
			column_wall(al, x, wall_size, over_hor, wall_height, texx, tex);
		}
		cur_hit++;
	}
	hit = ray->hits + cur_hit;
	wall_size = (hit->ce_hei - hit->fl_hei) * wall_scale
		/ hit->hitdst;
	wall_height = (hit->ce_hei - hit->fl_hei) * UINT16_MAX;
	over_hor = (ray->hits[ray->nb_hits - 1].ce_hei - al->play.eyez)
		* wall_scale / ray->hits[ray->nb_hits - 1].hitdst;
	tex = al->tex + ray->hits[ray->nb_hits - 1].wall.wall_tex;
	texx = ray->hits[ray->nb_hits - 1].hit_texx *
		al->tex[ray->hits[ray->nb_hits - 1].wall.wall_tex].size_x /
		SDL_MAX_UINT16;

	column_wall(al, x, wall_size, over_hor, wall_height, texx, tex);
}
