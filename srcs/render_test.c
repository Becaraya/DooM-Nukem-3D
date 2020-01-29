/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:07:39 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/28 15:47:56 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int			test_aleready_hit(t_rc_ray *ray, t_walls *owall)
{
	int i;

	i = 0;
	while (i < ray->nb_hits)
	{
		if (!ray->hits[i].is_entity)
			if ((ray->hits[i].wall.x1 == owall->x1 &&
					ray->hits[i].wall.y1 == owall->y1 &&
					ray->hits[i].wall.x2 == owall->x2 &&
					ray->hits[i].wall.y2 == owall->y2) ||
				(ray->hits[i].wall.x1 == owall->x2 &&
					ray->hits[i].wall.y1 == owall->y2 &&
					ray->hits[i].wall.x2 == owall->x1 &&
					ray->hits[i].wall.y2 == owall->y1))
				return (1);
		i++;
	}
	return (0);
}

void		wall_hit(t_al *al, t_rc_ray *ray, t_walls *wall, t_walls *owall)
{
	ray->hits[ray->nb_hits].is_entity = 0;
	ray->hits[ray->nb_hits].wall_length = wall_len(owall);
	wall->x1 > wall->x2 ? swapd(&wall->x1, &wall->x2) : 0;
	ray->hits[ray->nb_hits].hit_texx = (unsigned)(wall->x1 /
		(wall->x1 - wall->x2) * wall_len(owall) * UINT16_MAX) %
		(unsigned)(TEX_REPEAT * UINT16_MAX) / TEX_REPEAT;
	ray->hits[ray->nb_hits].wall = *owall;
	ray->hits[ray->nb_hits].transparent = owall->wall_tex ? 0 : 1;
	ray->hits[ray->nb_hits].tex = al->tex[owall->wall_tex];
}

int			test_hit(t_al *al, t_rc_ray *ray, t_walls *wall, t_walls *owall)
{
	double		alpha;
	double		beta;
	double		tmp_dst;

	if (((wall->x1 >= 0 && wall->x2 <= 0) ||
		(wall->x2 >= 0 && wall->x1 <= 0)) && wall->x1)
	{
		alpha = (wall->x2 - wall->x1) / (double)(wall->y2 - wall->y1);
		beta = wall->x1 - wall->y1 * alpha;
		tmp_dst = wall->y2 == wall->y1 ? 0 : -beta / alpha;
		if (tmp_dst > 0 && tmp_dst < ray->min)
			if (!test_aleready_hit(ray, owall))
			{
				ray->min = tmp_dst;
				tmp_dst *= al->cos[sub_angle(ray->angle, al->play.dir)];
				ray->hits[ray->nb_hits].hitdst = tmp_dst;
				wall_hit(al, ray, wall, owall);
				return (1);
			}
	}
	return (0);
}

int			test_ent_aleready_hit(t_rc_ray *ray, t_mob *oent)
{
	int i;

	i = 0;
	while (i < ray->nb_hits)
	{
		if (ray->hits[i].is_entity)
			if (ray->hits[i].ent.posx == oent->posx &&
				ray->hits[i].ent.posy == oent->posy &&
				ray->hits[i].ent.posz == oent->posz)
				return (1);
		i++;
	}
	return (0);
}

int			test_ent_hit(t_al *al, t_rc_ray *ray, t_mob *rotent, t_mob *oent)
{
	if (rotent->posx < oent->width / 2 && rotent->posx > -oent->width / 2)
	{
		if (rotent->posy > 0 && rotent->posy < ray->min && rotent->posy <
			ray->minent)
			if (!test_ent_aleready_hit(ray, oent))
			{
				ray->minent = rotent->posy;
				ray->min = rotent->posy;
				ray->hits[ray->nb_hits].is_entity = 1;
				ray->hits[ray->nb_hits].wall_length = oent->width;
				ray->hits[ray->nb_hits].hitdst = rotent->posy * al->cos[
					sub_angle(rotent->angle_to_player, al->play.dir)];
				ray->hits[ray->nb_hits].ent = *oent;
				ray->hits[ray->nb_hits].tex = find_ent_tex(al, oent);
				ray->hits[ray->nb_hits].hit_texx = (oent->width / 2 -
					rotent->posx) * ray->hits[ray->nb_hits].tex.size_x /
				oent->width;
				return (1);
			}
	}
	return (0);
}
