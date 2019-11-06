#include "doom-nukem.h"

unsigned int		**load_anim(t_al *al, char *path, int nb_tex)
{
	unsigned int	**pix;
	char			*name;
	int				i;

	i = -1;
	if (!(pix = ft_memalloc(sizeof(unsigned int	**) * nb_tex)))
		yeet(al);
	while (++i != (nb_tex))
	{
		name = ft_strjoin(path,ft_itoa(i + 1));
		name = ft_strjoinfreef(name,".bmp");
		// printf("path = %s\n",name);
		pix[i] = parse_tex(al, name, SPRITE_W, SPRITE_H);
		ft_strdel(&name);
	}
	ft_strdel(&path);
	return (pix);
}
// char	*ft_strjoinfreef(char *s1, char const *s2)

void		init_or(t_al *al, t_tex_group *texgrp, char *path)
{
	texgrp->or[0].pix = load_anim(al, ft_strjoin(path,"or1/"), texgrp->nb_tex);
	texgrp->or[1].pix = load_anim(al, ft_strjoin(path,"or2/"), texgrp->nb_tex);
	texgrp->or[2].pix = load_anim(al, ft_strjoin(path,"or3/"), texgrp->nb_tex);
	texgrp->or[3].pix = load_anim(al, ft_strjoin(path,"or4/"), texgrp->nb_tex);
	texgrp->or[4].pix = load_anim(al, ft_strjoin(path,"or5/"), texgrp->nb_tex);
	texgrp->or[5].pix = load_anim(al, ft_strjoin(path,"or6/"), texgrp->nb_tex);
	texgrp->or[6].pix = load_anim(al, ft_strjoin(path,"or7/"), texgrp->nb_tex);
	texgrp->or[7].pix = load_anim(al, ft_strjoin(path,"or8/"), texgrp->nb_tex);
	texgrp->or[8].pix = load_anim(al, ft_strjoin(path,"death/"), texgrp->nb_tex);
}

void	set_texgrp(t_al *al, int nb_tex, char *path, int index)
{
	al->texgp[index].size_x = SPRITE_W;
	al->texgp[index].size_y = SPRITE_H;
	al->texgp[index].nb_tex = nb_tex;
	init_or(al,&al->texgp[index], path);
}


void	init_texgrp(t_al *al)
{
	if (!(al->texgp = ft_memalloc(sizeof(t_tex_group) * al->nb_texgp)))
		yeet(al);
	set_texgrp(al,7,"ressources/sprite/",0);
}


void	display_texgp(t_al *al, unsigned int *pix)
{
	int x;
	int y;
	int i;

	i = -1;
	x = -1;
	// printf("start\n");
	while (++x < SPRITE_W)
	{
		y = -1;
		while (++y < SPRITE_H)
		{
			al->pix[x + (y * WIN_SIZEX) ] =	pix[++i];

		}
	}
}
