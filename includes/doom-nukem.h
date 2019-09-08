/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:24:16 by becaraya          #+#    #+#             */
/*   Updated: 2019/09/08 17:04:01 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <fcntl.h>
# include "libft.h"
# include <stdio.h>
// # include <math.h>
# include <mlx.h>
# include <sys/time.h>
# include <SDL.h>
# include <SDL_ttf.h>

# define WIN_TITLE "s     p     o     o     k     y"
# define WIN_SIZEX 1280
# define WIN_SIZEY 720
# define WIN_POSX 100
# define WIN_POSY 10

# define ST_GAME 1
# define ST_PAUSE 2
# define ST_MENU 3
# define ST_SETTING 4
# define ST_EDIT 5
# define ST_MAP_CUSTOME 6

/*
**TOOLS
*/

# define T_SELECT 1
# define T_WALL_1 2
# define T_WALL_2 3
# define T_WALL_3 4


typedef struct		s_keys
{
	unsigned		w:1;
	unsigned		a:1;
	unsigned		s:1;
	unsigned		d:1;
	unsigned		left:1;
	unsigned		righ:1;
	unsigned		up:1;
	unsigned		down:1;
	unsigned		lshift:1;
	unsigned		space:1;
	unsigned		ctrl:1;
}					t_keys;

typedef struct		s_mouse
{
	unsigned		left:1;
	unsigned		righ:1;
	unsigned		up:1;
	unsigned		down:1;
	unsigned		mouve:1;
	unsigned		click:1;
}					t_mouse;

typedef struct		s_icon
{
	unsigned int	*chest;
	unsigned int	*click;
	unsigned int	*path;
	unsigned int	*portal;
	unsigned int	*wall;
}					t_icon;

typedef struct		s_texture
{
	unsigned int	*s_menu;
	t_icon			ic;
}					t_texture;

typedef struct		s_point
{
	int				x;
	int				y;
	int				color;
}					t_point;

typedef struct		s_wall
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	struct s_wall	*prev;
	struct s_wall	*next;
}					t_wall;

typedef struct		s_edit
{
	int				stat;
	int				zoom;
}					t_edit;

typedef struct		s_al
{
	int				status;
	
	SDL_Window		*win;
	SDL_Texture		*tex;
	SDL_Renderer	*ren;
	unsigned int	*pix;

	char			fps;
	long			last_time;
	long			curr_time;
	long			tgt_time;
	int				dtime;

	t_edit			edit;

	t_keys			k;
	SDL_Event		ev;
	t_mouse			m;

	t_texture		txt;

	t_wall			*wall;
	int				c_wall;

	char			v0id[32];
}					t_al;

unsigned int		*parse_tex(t_al *al, char *name, int w, int h);

void				init(t_al *al);
void				main_loop(t_al *al);
void				edit(t_al *al);

void				key_func(t_al *al);
void				mouse_press(t_al *al);
void				mouse_func(t_al *al);

void				refresh(t_al *al);
int					yeet(t_al *al);

#endif