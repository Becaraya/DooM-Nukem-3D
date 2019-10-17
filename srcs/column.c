/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:46:13 by pitriche          #+#    #+#             */
/*   Updated: 2019/10/17 18:40:38 by pitriche         ###   ########.fr       */
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

inline int	tex_find(int *pix, int texx, int texy, t_tex *tex)
{
	int color;

	if (!((color = tex->pix[tex->size_x * texy + texx]) >> 24))
		*pix = color;
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
		tex_find(al->pix + (y * WIN_SIZEX + x), texx, texy, tex);
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
	if ((cur_hit = ray->nb_hits - 1) == -1)
		return ;
	wall_scale = 200 * D_2PI / al->fov;

	// ######################## floorcasting ###################################

	hit = ray->hits + cur_hit;
	int mapx, mapy, mapxor, mapyor, mapdstor, mapdst;
	mapdstor = al->play.eyez * UINT16_MAX * WIN_SIZEY;
	mapdstor /= al->cos[sub_angle(ray->angle, al->play.dir)];
	mapxor = al->play.posx * UINT16_MAX;
	mapyor = al->play.posy * UINT16_MAX;
	y = WIN_SIZEY / 2 + 1;
	while (y < WIN_SIZEY)
	{
		tex = al->tex + 1;
		mapdst = mapdstor;
		mapdst /= 2 * y - WIN_SIZEY;
		mapx = mapxor + mapdst * ray->xfact / UINT16_MAX;
		mapx = mapx >= 0 ? mapx % TEX_REPEAT_F :
		TEX_REPEAT_F + (mapx % TEX_REPEAT_F);
		mapx *= tex->size_x;
		mapy = mapyor + mapdst * ray->yfact / UINT16_MAX;
		mapy = mapy >= 0 ? mapy % TEX_REPEAT_F :
		TEX_REPEAT_F + (mapy % TEX_REPEAT_F);
		mapy *= tex->size_y;

		//tex_find(al->pix + WIN_SIZEX * 0 + 0, 0, 0, al->tex + 2);
		tex_find(al->pix + WIN_SIZEX * y + x, mapx / TEX_REPEAT_F, mapy /
		 	TEX_REPEAT_F, tex);
		y++;
	}

	// ######################## wallcasting ####################################

	hit = ray->hits + cur_hit;
	wall_height = (hit->ce_hei - hit->fl_hei) * UINT16_MAX;
	over_hor = (hit->ce_hei - al->play.eyez) * wall_scale / hit->hitdst;
	wall_size = over_hor - ((hit->fl_hei - al->play.eyez) * wall_scale /
		hit->hitdst);
	tex = al->tex + hit->wall.wall_tex;
	texx = hit->hit_texx * tex->size_x / SDL_MAX_UINT16;
	column_wall(al, x, wall_size, over_hor, wall_height, texx, tex);

	while (cur_hit--)
	{
		hit = ray->hits + cur_hit;
		// top walls
		if ((wall_height = (hit->ce_hei - ray->hits[cur_hit + 1].ce_hei) *
				UINT16_MAX) > 0)
		{
			wall_size = (hit->ce_hei - ray->hits[cur_hit + 1].ce_hei) *
				wall_scale / hit->hitdst;
			over_hor = (hit->ce_hei - al->play.eyez) * wall_scale / hit->hitdst;
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
			over_hor = (hit->fl_hei - al->play.eyez) * wall_scale / hit->hitdst
				+ wall_size;
			tex = al->tex + hit->wall.bot_tex;
			texx = hit->hit_texx * tex->size_x / SDL_MAX_UINT16;
			column_wall(al, x, wall_size, over_hor, wall_height, texx, tex);
		}
	}
}
