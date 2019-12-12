/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:46:13 by pitriche          #+#    #+#             */
/*   Updated: 2019/12/12 02:42:08 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

int	skybox(t_al *al, int y, int tx)
{
	int ty;

	ty = al->tex[0].size_y * (y + al->play.horizon + HORIZON_LIMIT)
	/ al->stretch;
	return (al->tex[0].pix[ty * al->tex[0].size_x + tx]);
}

int	tex_find(unsigned int *pix, int texx, int texy, t_tex *tex)
{
	int color;

	if ((color = tex->pix[tex->size_x * texy + texx]) >> 24)
		*pix = color;
	else
	{
		//printf("%#010x\n", color);
		return (1);
	}
	return (0);
}

/*
** #############################################################################
*/

void		hit_floor(t_al *al, t_rc_ray *ray, int hitnb)
{
	t_floorcast	f;
	t_tex		*tex;
	int			y;
	long		tmp;

	tex = al->tex + ray->hits[hitnb].fl_tex;
	y = ray->hits[hitnb].lim.sc_botwall;
	f.posx = al->play.posx * UINT16_MAX * al->fov;
	f.posy = al->play.posy * UINT16_MAX * al->fov;
	f.hor = al->play.horizon + HORIZON_LIMIT;
	f.indst = UINT16_MAX * (al->play.eyez - ray->hits[hitnb].fl_hei) *
	al->stretch / al->cos[sub_angle(ray->angle, al->play.dir)];
	while (y < ray->hits[hitnb].lim.sc_botlim)
	{
		tmp = (2 * (y + f.hor) - al->stretch);
		tmp = tmp ? f.indst / tmp : UINT16_MAX;
		f.dstx = tmp * ray->xfact / UINT16_MAX + f.posx * 1.04;
		f.dsty = tmp * ray->yfact / UINT16_MAX + f.posy * 1.04;
		f.dstx = ((f.dstx & TEX_REPEAT_F) * tex->size_x) >> TEX_REPEAT_F_DIV;
		f.dsty = ((f.dsty & TEX_REPEAT_F) * tex->size_y) >> TEX_REPEAT_F_DIV;
		tmp = f.dsty * tex->size_x + f.dstx;
		al->pix[y * WIN_SIZEX + ray->x] = (tex->pix[tmp] >> 24) ? tex->pix[tmp]
		: skybox(al, y, 0);
		y-=-1;
	}
}

void		hit_ceiling(t_al *al, t_rc_ray *ray, int hitnb)
{
	t_floorcast	f;
	t_tex		*tex;
	int			y;
	long		tmp;

	tex = al->tex + ray->hits[hitnb].ce_tex;
	y = ray->hits[hitnb].lim.sc_toplim;
	f.posx = al->play.posx * UINT16_MAX * al->fov;
	f.posy = al->play.posy * UINT16_MAX * al->fov;
	f.hor = al->play.horizon + HORIZON_LIMIT;
	f.indst = UINT16_MAX * (ray->hits[hitnb].ce_hei - al->play.eyez) *
	al->stretch / al->cos[sub_angle(ray->angle, al->play.dir)];
	while (y < ray->hits[hitnb].lim.sc_topwall)
	{
		tmp = al->stretch - 2 * (y + f.hor);
		tmp = tmp ? f.indst / tmp : UINT16_MAX;
		f.dstx = tmp * ray->xfact / UINT16_MAX + f.posx * 1.04;
		f.dsty = tmp * ray->yfact / UINT16_MAX + f.posy * 1.04;
		f.dstx = ((f.dstx & TEX_REPEAT_F) * tex->size_x) >> TEX_REPEAT_F_DIV;
		f.dsty = ((f.dsty & TEX_REPEAT_F) * tex->size_y) >> TEX_REPEAT_F_DIV;
		tmp = f.dsty * tex->size_x + f.dstx;
		al->pix[y * WIN_SIZEX + ray->x] = (tex->pix[tmp] >> 24) ? tex->pix[tmp]
		: skybox(al, y, 0);
		y-=-1;
	}
}

void		hit_top_wall(t_al *al, t_rc_ray *ray, int hitnb)
{
	t_rc_hit	*hit;
	t_tex		*tex;
	t_rc_lim	*lim;
	int			tot_length;
	int			y;

	hit = ray->hits + hitnb;
	tex = &hit->tex;
	lim = &hit->lim;
	tot_length = lim->topmid - lim->topwall;
	y = lim->sc_topwall;
	//if (ray->x == WIN_SIZEX / 2)
	//	printf("there %d in [%d>%d]\n", y, lim->botmid, lim->botwall);
	while (y < lim->sc_topmid)
	{
		tex_find(al->pix + y * WIN_SIZEX + ray->x, ray->hits[hitnb].hit_texx *
			tex->size_x / UINT16_MAX, (((y - lim->topwall) * hit->topwall_he /
						tot_length) % TEX_REPEAT_F) * tex->size_y /
				TEX_REPEAT_F, tex);
		y-=-1;
	}
}

void		hit_bot_wall(t_al *al, t_rc_ray *ray, int hitnb)
{
	t_rc_hit	*hit;
	t_tex		*tex;
	t_rc_lim	*lim;
	int			tot_length;
	int			y;

	hit = ray->hits + hitnb;
	tex = &hit->tex;
	lim = &hit->lim;
	tot_length = lim->botwall - lim->botmid;
	y = lim->sc_botmid;
	//if (ray->x == WIN_SIZEX / 2)
	//	printf("there %d in [%d>%d]\n", y, lim->botmid, lim->botwall);
	while (y < lim->sc_botwall)
	{
		tex_find(al->pix + y * WIN_SIZEX + ray->x, ray->hits[hitnb].hit_texx *
			tex->size_x / UINT16_MAX, (((y - lim->botmid) * hit->botwall_he /
						tot_length) % TEX_REPEAT_F) * tex->size_y /
				TEX_REPEAT_F, tex);
		y-=-1;
	}
}

void		hit_wall(t_al *al, t_rc_ray *ray, int hitnb)
{
	t_rc_hit	*hit;
	t_tex		*tex;
	t_rc_lim	*lim;
	int			tot_length;
	int			y;

	hit = ray->hits + hitnb;
	if (hit->transparent)
		return ;
	tex = &hit->tex;
	lim = &hit->lim;
	tot_length = lim->botmid - lim->topmid;
	y = lim->sc_topmid;
	//if (ray->x == WIN_SIZEX / 2)
	//	printf("there %d in [%d>%d]\n", y, lim->botmid, lim->botwall);
	while (y < lim->sc_botmid)
	{
		tex_find(al->pix + y * WIN_SIZEX + ray->x, ray->hits[hitnb].hit_texx *
			tex->size_x / UINT16_MAX, (((y - lim->topmid) * hit->wall_he /
						tot_length) % TEX_REPEAT_F) * tex->size_y /
				TEX_REPEAT_F, tex);
		y-=-1;
	}
}

/*
** #############################################################################
*/

/*
** je pete des cables putain
*/

void	cap_int(int *var, int lowcap, int highcap)
{
	if (*var < lowcap)
		*var = lowcap;
	if (*var > highcap)
		*var = highcap;
}

/*
** je noie ma souffrance dans l'alcool
*/

void		sc_lims(t_rc_lim *lim, t_rc_lim prlim)
{
	lim->sc_toplim = lim->toplim;
	cap_int(&lim->sc_toplim, prlim.mb_toplim, prlim.mb_botlim);
	lim->sc_topwall = lim->topwall;
	cap_int(&lim->sc_topwall, prlim.mb_toplim, prlim.mb_botlim);
	lim->sc_topmid = lim->topmid;
	cap_int(&lim->sc_topmid, prlim.mb_toplim, prlim.mb_botlim);
	
	lim->sc_botlim = lim->botlim;
	cap_int(&lim->sc_botlim, prlim.mb_toplim, prlim.mb_botlim);
	lim->sc_botwall = lim->botwall;
	cap_int(&lim->sc_botwall, prlim.mb_toplim, prlim.mb_botlim);
	lim->sc_botmid = lim->botmid;
	cap_int(&lim->sc_botmid, prlim.mb_toplim, prlim.mb_botlim);
	lim->mb_toplim = lim->sc_topmid;
	lim->mb_botlim = lim->sc_botmid;
}

void		hit_ent(t_al *al, t_rc_ray *ray, int hitnb)
{
	t_tex		*tex;
	t_rc_lim	*lim;
	int			tot_length;
	int			y;

	tex = &ray->hits[hitnb].tex;
	lim = &ray->hits[hitnb].lim;
	tot_length = lim->botmid - lim->topmid;
	y = lim->sc_topmid;
	//if (ray->x == WIN_SIZEX / 2)
	//	printf("tot %d\n", tot_length);
	while (y < lim->sc_botmid)
	{
		tex_find(al->pix + y * WIN_SIZEX + ray->x, ray->hits[hitnb].hit_texx,
		(y - lim->topmid) * tex->size_y / tot_length, tex);
		y-=-1;
	}
}

unsigned	new_wall_he(t_al *al, t_rc_hit *hit, t_rc_hit *nhit)
{
	double ceil;
	double floor;

	ceil = hit->ce_hei > nhit->ce_hei ? nhit->ce_hei : hit->ce_hei;
	floor = hit->fl_hei < nhit->fl_hei ? nhit->fl_hei : hit->fl_hei;
	return ((unsigned)((ceil - floor) * UINT16_MAX));
}

void		hit_print(t_al *al, t_rc_ray *ray, int hitnb, t_rc_lim prlim)
{
	t_rc_hit	*hit;
	t_rc_lim	*lim;
	int			hor;

	hit = ray->hits + hitnb;
	lim = &hit->lim;
	hor = WIN_SIZEY / 2 - al->play.horizon;
	if (!hit->is_entity)
	{
		hit->wall_he = (hit->ce_hei - hit->fl_hei) * UINT16_MAX;
		lim->toplim = prlim.mb_toplim;
		lim->topwall = hor - ((hit->ce_hei - al->play.eyez) *
			al->wall_scale / hit->hitdst);
		lim->topmid = lim->topwall;
		lim->botlim = prlim.mb_botlim;
		lim->botwall = hor + ((al->play.eyez - hit->fl_hei) *
			al->wall_scale / hit->hitdst);
		lim->botmid = lim->botwall;
		if (hitnb < ray->nb_hits - 1)
		{
			hit->wall_he = new_wall_he(al, hit, hit + 1);
			lim->topmid = hit->ce_hei > (hit + 1)->ce_hei ? hor -
			((hit + 1)->ce_hei - al->play.eyez) * al->wall_scale / hit->hitdst
			: lim->topwall;
			hit->topwall_he = hit->ce_hei > (hit + 1)->ce_hei ? (hit->ce_hei -
			(hit + 1)->ce_hei) * UINT16_MAX : 0;
			lim->botmid = hit->fl_hei < (hit + 1)->fl_hei ? hor +
			(al->play.eyez - (hit + 1)->fl_hei) * al->wall_scale / hit->hitdst
			: lim->botwall;
			hit->botwall_he = hit->fl_hei < (hit + 1)->fl_hei ?
			((hit + 1)->fl_hei - hit->fl_hei) * UINT16_MAX : 0;
		}
		sc_lims(lim, prlim);
		hit_ceiling(al, ray, hitnb);
		hit_floor(al, ray, hitnb);
		if (hitnb < ray->nb_hits - 1)
		{
			hit_top_wall(al, ray, hitnb);
			hit_bot_wall(al, ray, hitnb);
		}
	}
	else
	{
		lim->topmid = hor + ((al->play.eyez - (hit->ent.posz + hit->ent.size)) *
			al->wall_scale / hit->hitdst);
		lim->botmid = hor - ((hit->ent.posz - al->play.eyez) *
			al->wall_scale / hit->hitdst);
		sc_lims(lim, prlim);
	}
	if (hitnb < ray->nb_hits - 1)
		hit_print(al, ray, hitnb + 1, hit->is_entity ? prlim : *lim);
	hit->is_entity ? hit_ent(al, ray, hitnb) : hit_wall(al, ray, hitnb);
}



void		column(t_al *al, t_rc_ray *ray)
{
	t_rc_lim lim;

	lim.mb_toplim = 0;
	lim.mb_botlim = WIN_SIZEY - 1;
	hit_print(al, ray, 0, lim);
}

/*
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
	if (!tex)
		return ;
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

void		column(t_al *al, t_rc_ray *ray)
{
	int cur_hit;
	int tx;
	int y;
	int x = ray->x;
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

	// number in the end is sliding correction
	posx = al->play.posx * UINT16_MAX * al->fov * 0.0008423;
	posy = al->play.posy * UINT16_MAX * al->fov * 0.0008423;
	horizon = al->play.horizon + HORIZON_LIMIT + 1;
	correct = al->cos[sub_angle(ray->angle, al->play.dir)];
	initdst = UINT16_MAX * al->stretch / correct * (al->play.eyez -
		hit->fl_hei);
	while (y < WIN_SIZEY && initdst > 0)
	{
		dist = !(tmp = (2 * (y + horizon) - al->stretch)) ? UINT16_MAX :
		initdst / tmp;
		distx = dist * ray->xfact / UINT16_MAX + posx;
		distx = ((distx & TEX_REPEAT_F) * tex->size_x) >> 17;
		disty = dist * ray->yfact / UINT16_MAX + posy;
		disty = ((disty & TEX_REPEAT_F) * tex->size_y) >> 17;
		tmp = disty * tex->size_x + distx;
		al->pix[y * WIN_SIZEX + x] = (tex->pix[tmp] >> 24) ? tex->pix[tmp] :
		skybox(al, y, tx);
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

		tmp = disty * tex->size_x + distx;
		al->pix[y * WIN_SIZEX + x] = (tex->pix[tmp] >> 24) ? tex->pix[tmp] :
		skybox(al, y, tx);
		y++;
	}

	// ######################## hits ###########################################
	while (cur_hit--)
	{
		hit = ray->hits + cur_hit;
		//middle walls
		distx = ray->hits[cur_hit + 1].fl_hei > hit->fl_hei ?
		ray->hits[cur_hit + 1].fl_hei : hit->fl_hei;
		disty = ray->hits[cur_hit + 1].ce_hei < hit->ce_hei ?
		ray->hits[cur_hit + 1].ce_hei : hit->ce_hei;
		if ((wall_height = (disty - distx) * UINT16_MAX) > 0)
		{
			wall_size = (disty - distx) *
				wall_scale / hit->hitdst;
			over_hor = (distx - al->play.eyez) * wall_scale / hit->hitdst
				+ wall_size;
			tex = hit->wall.wall_tex ? al->tex + hit->wall.wall_tex : 0;
			texx = tex ? hit->hit_texx * tex->size_x / UINT16_MAX : 0;
			column_wall(al, x, wall_size, over_hor, wall_height, 0, texx, tx, hit, tex);
		}
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
			tmp = disty * tex->size_x + distx;
			al->pix[y * WIN_SIZEX + x] = (tex->pix[tmp] >> 24) ? tex->pix[tmp] :
			skybox(al, y, tx);
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
			tmp = disty * tex->size_x + distx;
			al->pix[y * WIN_SIZEX + x] = (tex->pix[tmp] >> 24) ? tex->pix[tmp] :
			skybox(al, y, tx);
			y++;
		}
	}
}*/
