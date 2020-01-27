/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:04:26 by becaraya          #+#    #+#             */
/*   Updated: 2020/01/25 11:49:07 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			draw_triangle(t_point p, int i, SDL_Surface *surf, int color)
{
	t_point		a;
	t_point		b;

	a.x = p.x;
	a.y = p.y - 8;
	while (a.y <= p.y + 8)
	{
		b.y = a.y;
		b.x = a.x + i;
		if (i > 0)
			i += (a.y >= p.y) ? -1 : 1;
		else
			i -= (a.y >= p.y) ? -1 : 1;
		ft_put_line(a, b, surf, color);
		a.y++;
	}
}

void			ft_put_line(t_point a, t_point b, SDL_Surface *surf, int color)
{
	t_point		delta;
	t_point		sign;
	t_point		cur;
	int			tab[2];

	delta.x = ft_abs(b.x - a.x);
	delta.y = ft_abs(b.y - a.y);
	sign.x = a.x < b.x ? 1 : -1;
	sign.y = a.y < b.y ? 1 : -1;
	tab[0] = delta.x - delta.y;
	cur = a;
	while (cur.x != b.x || cur.y != b.y)
	{
		((int *)surf->pixels)[cur.x + cur.y * surf->w] = color;
		if ((tab[1] = tab[0] * 2) > -delta.y)
		{
			tab[0] -= delta.y;
			cur.x += sign.x;
		}
		if (tab[1] < delta.x)
		{
			tab[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

void			put_rectangle(SDL_Surface *surf, t_point a, t_point b, int clr)
{
	t_point		c;
	t_point		d;

	c.x = a.x;
	c.y = b.y;
	d.x = b.x;
	d.y = a.y;
	ft_put_line(a, d, surf, clr);
	c.y++;
	ft_put_line(a, c, surf, clr);
	c.y--;
	ft_put_line(d, b, surf, clr);
	ft_put_line(b, c, surf, clr);
}
