/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:24:16 by becaraya          #+#    #+#             */
/*   Updated: 2019/08/22 12:50:02 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <fcntl.h>
# include "libft.h"
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <sys/time.h>
# include "SDL.h"

# define WIN_TITLE "s     p     o     o     k     y"
# define WIN_SIZEX 1280
# define WIN_SIZEY 720
// # define WIN_POSX 100
// # define WIN_POSY 10

# define ST_GAME 1
# define ST_PAUSE 2
# define ST_MENU 3
# define ST_SETTING 4

typedef struct		s_keys
{
	unsigned	w:1;
	unsigned	a:1;
	unsigned	s:1;
	unsigned	d:1;
	unsigned	left:1;
	unsigned	righ:1;
	unsigned	up:1;
	unsigned	down:1;
	unsigned	lshift:1;
	unsigned	space:1;
	unsigned	ctrl:1;
}					t_keys;

typedef struct		s_mouse
{
	unsigned	left:1;
	unsigned	righ:1;
	unsigned	up:1;
	unsigned	down:1;
	unsigned	mouve:1;
	unsigned	click:1;
}					t_mouse;

typedef struct		s_al
{
	int				status;

	SDL_Window		*win;
	SDL_Texture		*tex;
	SDL_Renderer	*ren;
	unsigned int	*pix;

	t_keys			k;
	SDL_Event		ev;
	t_mouse			m;
}					t_al;

unsigned int	*parse_tex(t_al *al, char *name);

int				yeet(t_al *al);

#endif