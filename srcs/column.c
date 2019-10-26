/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:46:13 by pitriche          #+#    #+#             */
/*   Updated: 2019/10/24 17:08:10 by pitriche         ###   ########.fr       */
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

inline int	tex_find(unsigned int *pix, int texx, int texy, t_tex *tex)
{
	int color;

	if ((color = tex->pix[tex->size_x * texy + texx]) >> 24)
		*pix = color;
	else
		return (1);
	return (0);
}

void		column_wall(t_al *al, int x, int wall_size, int over_hor,
	int wall_heigth, int mbt, int texx, int tx, t_rc_hit *hit, t_tex *tex)
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
	if (mbt == 0 || mbt == 2)
		hit->w_toplim = y < WIN_SIZEY ? y : WIN_SIZEY - 1;
	ymax = (WIN_SIZEY / 2) - al->play.horizon - over_hor + wall_size;
	yormax = ymax;
	texymax = yormax - yor;
	ymax = ymax > WIN_SIZEY ? WIN_SIZEY : ymax;
	if (mbt == 0 || mbt == 1)
		hit->w_botlim = ymax;
	while (y < ymax)
	{
	//printf("((y - yor) * wall_heigth / texymax) > %u\n", (y - yor) * wall_heigth / texymax);
		texy = ((((y - yor) * wall_heigth / texymax) % TEX_REPEAT_V) *
			tex->size_y) / TEX_REPEAT_V;
		tex_find(al->pix + (y * WIN_SIZEX + x), texx, texy, tex) ?
		al->pix[y * WIN_SIZEX + x] = skybox(al, y, tx) : 0;
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
	//while (++y < WIN_SIZEY)
	//	al->pix[y * WIN_SIZEX + x] = skybox(al, y, tx);
	if ((cur_hit = ray->nb_hits - 1) == -1)
		return ;
	wall_scale = 200 * D_2PI / al->fov;

	hit = ray->hits + cur_hit;

	// ######################## wallcasting ####################################

	wall_height = (hit->ce_hei - hit->fl_hei) * UINT16_MAX;
	over_hor = (hit->ce_hei - al->play.eyez) * wall_scale / hit->hitdst;
	wall_size = over_hor - ((hit->fl_hei - al->play.eyez) * wall_scale /
		hit->hitdst);
	tex = al->tex + hit->wall.wall_tex;
	texx = hit->hit_texx * tex->size_x / UINT16_MAX;
	column_wall(al, x, wall_size, over_hor, wall_height, 0, texx, tx, hit, tex);


	// ######################## floorcasting ###################################

	int horizon, initdst, ymax, tmp;
	double correct;
	long dist, distx, disty, posx, posy;

	tex = al->tex + hit->fl_tex;
	y = hit->w_botlim <= 0 ? 0 : hit->w_botlim;

	// number in the end is sliding correction calculation
	posx = al->play.posx * UINT16_MAX * al->fov * 0.0008423;
	posy = al->play.posy * UINT16_MAX * al->fov * 0.0008423;
	horizon = al->play.horizon + HORIZON_LIMIT + 1;
	correct = al->cos[sub_angle(ray->angle, al->play.dir)];
	initdst = UINT16_MAX * al->stretch / correct * (al->play.eyez -
		hit->fl_hei);
	while (y < WIN_SIZEY)
	{
		dist = !(tmp = (2 * (y + horizon) - al->stretch)) ? UINT16_MAX :
		initdst / tmp;

		distx = dist * ray->xfact / UINT16_MAX + posx;
		distx = ((distx & TEX_REPEAT_F) * tex->size_x) >> 17;

		disty = dist * ray->yfact / UINT16_MAX + posy;
		disty = ((disty & TEX_REPEAT_F) * tex->size_y) >> 17;

		al->pix[y * WIN_SIZEX + x] = tex->pix[disty * tex->size_x + distx];
		y++;
	}
	// ######################## ceilcasting ####################################

	tex = al->tex + hit->ce_tex;
	y = 0;
	ymax = hit->w_toplim >= WIN_SIZEY ? WIN_SIZEY - 1 : hit->w_toplim;
	initdst = UINT16_MAX * al->stretch / correct * (hit->ce_hei -
		al->play.eyez);
	while (y < ymax)
	{
		dist = !(tmp = (al->stretch - 2 * (y + horizon))) ? UINT16_MAX :
		initdst / tmp;

		distx = dist * ray->xfact / UINT16_MAX + posx;
		distx = ((distx & TEX_REPEAT_F) * tex->size_x) >> 17;

		disty = dist * ray->yfact / UINT16_MAX + posy;
		disty = ((disty & TEX_REPEAT_F) * tex->size_y) >> 17;

		al->pix[y * WIN_SIZEX + x] = tex->pix[disty * tex->size_x + distx];
		y++;
	}

	// ######################## hits ###########################################
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
			texx = hit->hit_texx * tex->size_x / UINT16_MAX;
			column_wall(al, x, wall_size, over_hor, wall_height, 2, texx, tx, hit, tex);
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
			texx = hit->hit_texx * tex->size_x / UINT16_MAX;
			column_wall(al, x, wall_size, over_hor, wall_height, 1, texx, tx, hit, tex);
		}

		// ######################## floorcasting ###################################

		tex = al->tex + hit->fl_tex;
		y = hit->w_botlim <= 0 ? 0 : hit->w_botlim;
		// number in the end is sliding correction
		posx = al->play.posx * UINT16_MAX * al->fov * 0.0008423;
		posy = al->play.posy * UINT16_MAX * al->fov * 0.0008423;
		horizon = al->play.horizon + HORIZON_LIMIT + 1;
		correct = al->cos[sub_angle(ray->angle, al->play.dir)];
		initdst = UINT16_MAX * al->stretch / correct * (al->play.eyez - hit->fl_hei);
		while (y < WIN_SIZEY)
		{
			dist = !(tmp = (2 * (y + horizon) - al->stretch)) ? UINT16_MAX :
			initdst / tmp;

			distx = dist * ray->xfact / UINT16_MAX + posx;
			distx = ((distx & TEX_REPEAT_F) * tex->size_x) >> 17;

			disty = dist * ray->yfact / UINT16_MAX + posy;
			disty = ((disty & TEX_REPEAT_F) * tex->size_y) >> 17;

			//!x ? printf("%d x%d y%d\n", distx / UINT16_MAX - disty / UINT16_MAX, distx / UINT16_MAX, disty / UINT16_MAX) : 0;
			//y < 0 ? printf("A\n") : 0;
			//distx < 0 || distx >= tex->size_x || disty < 0 || disty >= tex->size_y ? printf("A\n") : 0;
			al->pix[y * WIN_SIZEX + x] = tex->pix[disty * tex->size_x + distx];
			y++;
		}

		// CEIL

		tex = al->tex + hit->ce_tex;
		y = 0;
		ymax = hit->w_toplim >= WIN_SIZEY ? WIN_SIZEY - 1 : hit->w_toplim;
		initdst = UINT16_MAX * al->stretch / correct * (hit->ce_hei -
		al->play.eyez);
		while (y < ymax)
		{
			dist = !(tmp = (al->stretch - 2 * (y + horizon))) ? UINT16_MAX :
			initdst / tmp;
			distx = dist * ray->xfact / UINT16_MAX + posx;
			distx = ((distx & TEX_REPEAT_F) * tex->size_x) >> 17;

			disty = dist * ray->yfact / UINT16_MAX + posy;
			disty = ((disty & TEX_REPEAT_F) * tex->size_y) >> 17;

			y < 0 || y >= WIN_SIZEY ? printf("y%d\n", y) : 0;
			al->pix[y * WIN_SIZEX + x] = tex->pix[disty * tex->size_x + distx];
			y++;
		}

	}
}
