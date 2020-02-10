/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_troy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 16:28:11 by hutricot          #+#    #+#             */
/*   Updated: 2020/02/06 15:18:59 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			load_hud(t_al *al)
{
	bmp_to_tex(&(al->h), "ressources/HUD/heart.bmp", 46, 41);
	bmp_to_tex(&(al->weapon[0]), "ressources/weapon/shotgun1.bmp", 102, 85);
	bmp_to_tex(&(al->weapon[1]),
		"ressources/weapon/shotgun_fire.bmp", 102, 105);
	bmp_to_tex(&(al->weapon[2]),
		"ressources/weapon/shotgun_fire2.bmp", 118, 150);
	bmp_to_tex(&(al->weapon[3]), "ressources/weapon/shotgun2.bmp", 118, 131);
	bmp_to_tex(&(al->weapon[4]), "ressources/weapon/shotgun3.bmp", 160, 140);
	bmp_to_tex(&(al->weapon[5]), "ressources/weapon/shotgun4.bmp", 160, 176);
	bmp_to_tex(&(al->weapon[6]), "ressources/weapon/shotgun5.bmp", 133, 172);
	al->f = al->weapon[0];
}

void			im_not_going_to_hell_for_this(t_al *al, int ipix)
{
	int				i;

	i = 0;
	while (i < 8)
	{
		if (al->mob_death[i].pix[ipix] != 0xffff)
			al->mob_death[i].pix[ipix] |= 0xff000000;
		i++;
	}
}

void			load_death(t_al *al)
{
	unsigned		i;

	bmp_to_tex(&al->you_died, "ressources/you_died.bmp", 518, 93);
	bmp_to_tex(&al->you_win, "ressources/you_win.bmp", 518, 93);
	bmp_to_tex(al->mob_death + 0, "ressources/mob_death/0.bmp", 512, 512);
	bmp_to_tex(al->mob_death + 1, "ressources/mob_death/1.bmp", 512, 512);
	bmp_to_tex(al->mob_death + 2, "ressources/mob_death/2.bmp", 512, 512);
	bmp_to_tex(al->mob_death + 3, "ressources/mob_death/3.bmp", 512, 512);
	bmp_to_tex(al->mob_death + 4, "ressources/mob_death/4.bmp", 512, 512);
	bmp_to_tex(al->mob_death + 5, "ressources/mob_death/5.bmp", 512, 512);
	bmp_to_tex(al->mob_death + 6, "ressources/mob_death/6.bmp", 512, 512);
	bmp_to_tex(al->mob_death + 7, "ressources/mob_death/7.bmp", 512, 512);
	i = 0;
	if (al->mob_death[0].size_x == 512 && al->mob_death[1].size_x == 512 &&
		al->mob_death[2].size_x == 512 && al->mob_death[3].size_x == 512 &&
		al->mob_death[4].size_x == 512 && al->mob_death[5].size_x == 512 &&
		al->mob_death[6].size_x == 512 && al->mob_death[7].size_x == 512)
		while (i < 262144)
		{
			im_not_going_to_hell_for_this(al, i);
			i++;
		}
}

void			load_goret(t_tex_group *tgp)
{
	unsigned	or;
	unsigned	i;
	char		str[28];

	tgp->nb_tex = 4;
	tgp->size_x = 512;
	tgp->size_y = 512;
	or = 0;
	ft_strcpy(str, "ressources/sprite/or1/1.bmp");
	ft_putstr("Loading [");
	while (or < 8)
	{
		if (!(tgp->or[or].pix = ft_memalloc(tgp->nb_tex * sizeof(unsigned *))))
			exit(pr_err(MERROR_MESS));
		str[20] = or + '1';
		i = 0;
		while (i < tgp->nb_tex)
		{
			str[22] = i + '1';
			bmp_to_pix(tgp->or[or].pix + i, str, 512, 512);
			javoue_jabuse1(tgp, i++, or);
		}
		or++;
	}
	ft_putstr("]\n");
}

void			init_textures(t_al *al)
{
	static unsigned i = 0;

	load_hud(al);
	load_death(al);
	if (!al->tex)
	{
		al->nb_tex = 3;
		if (!(al->tex = ft_memalloc((al->nb_tex + 1) * sizeof(t_tex))))
			exit(0);
		bmp_to_tex(al->tex + 0, "ressources/skybox.bmp", 32, 32);
		bmp_to_tex(al->tex + 1, "ressources/wall_tex.bmp", 800, 800);
		bmp_to_tex(al->tex + 2, "ressources/floor_tex.bmp", 950, 950);
		bmp_to_tex(al->tex + 3, "ressources/ceiling_tex.bmp", 512, 512);
		if (al->tex[0].pix[0] != 0xffff00ff)
			while (i < 32 * 32)
				al->tex[0].pix[i++] |= 0xff000000;
	}
	if (!al->texgp)
	{
		al->nb_texgp = 1;
		if (!(al->texgp = ft_memalloc(al->nb_texgp * sizeof(t_tex_group))))
			exit(0);
		load_goret(al->texgp);
	}
}
