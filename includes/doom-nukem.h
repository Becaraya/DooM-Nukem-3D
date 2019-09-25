/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:24:16 by becaraya          #+#    #+#             */
/*   Updated: 2019/09/24 11:46:53 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <fcntl.h>
# include "libft.h"
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include <SDL.h>

# define WIN_TITLE "100% totally mario sunshine virus free i swear"
# define WIN_SIZEX 1280
# define WIN_SIZEY 720
# define WIN_POSX 100
# define WIN_POSY 10

# define DEFAULT_G 9.81
# define DEFAULT_FOV 2

# define PLAYER_SIZE 178
# define PLAYER_MASS 67
# define PLAYER_AERO_POWER 400
# define PLAYER_ANA_POWER 950
# define LOOK_SENS 1.0

/*# define ST_GAME 1
# define ST_PAUSE 2
# define ST_MENU 3
# define ST_SETTING 4
# define ST_EDIT 5
# define ST_MAP_CUSTOME 6*/

# define MERROR_MESS "Malloc error\n"

/*
** TOOLS (?)
*/

# define M_2PI 6.283185307179586476925286766559005768394338798750211641949

# define T_SELECT 1
# define T_WALL_DRAWING 2
# define T_WALL_IDLE 3
# define T_WALL_3 4

# define MAX_IMGSIZE 10000


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

typedef enum		e_status
{
	MENU,
	GAME,
	PAUSE,
	EDIT
}					t_status;

/*
** horizontal force descripting struct, adding z force vector could be done
** but is useless for our usage
*/

typedef struct		s_force
{
	double	x;
	double	y;
}					t_force;

/*
** Player info struct
** Velocities are in m/s, positions are in cm (could be switched to meters at
** the extent of clarity with map), mass is in kg and power is in watt
*/

typedef struct		s_player
{
	double		posx;
	double		posy;
	double		posz;
	double		velx;
	double		vely;
	double		velz;
	double		gd_vel;

	double		size;
	double		mass;
	double		power;
	double		power_mult;

	double		dir;
	double		look_up;
	unsigned	on_ground:1;
}					t_player;

/*
** From here, all types are for the .hms parser and hence the game data
*/

typedef struct		s_walls
{
	signed int		x1;
	signed int		y1;
	signed int		x2;
	signed int		y2;
	unsigned short	wall_tex;
	unsigned short	top_tex;
	unsigned short	bot_tex;
	unsigned short	is_cross;
	unsigned int	sec_lnk;
}					t_walls;

typedef struct		s_tex
{
	unsigned int	size_x;
	unsigned int	size_y;
	unsigned int	*pix;
}					t_tex;

/*
**	fl:floor ce:ceiling hei:height tex:texture index
*/

typedef struct		s_sector
{
	unsigned int	fl_hei;
	unsigned int	ce_hei;
	unsigned short	fl_tex;
	unsigned short	ce_tex;
	unsigned int	nb_wal;
	t_walls			*walls;
}					t_sector;

/*
** Main structure #############################################################
*/

typedef struct		s_al
{
	t_status		status;
	void			(*stat_fnc[4])(struct s_al *);

	SDL_Window		*sdlwin;
	SDL_Texture		*sdltex;
	SDL_Renderer	*sdlren;
	unsigned int	*pix;

	unsigned int	nb_sec;
	t_sector		*sec;
	unsigned short	nb_tex;
	t_tex			*tex;

	double			g;
	t_player		play;
	double			fov;

	char			fps;
	long			last_time;
	long			curr_time;
	long			tgt_time;
	int				dtime;

	t_edit			edit;

	t_keys			k;
	SDL_Event		ev;
	t_mouse			m;

	t_wall			*wall;
	int				c_wall;

	char			v0id[32];
}					t_al;

/*
** Prototypes
*/

unsigned int		*parse_tex(t_al *al, char *name, int w, int h);
int					hms_parser(t_al *al, char *str);
int					pr_err(char *str);

void				init(t_al *al, char *str);
void				main_loop(t_al *al);

void				key_func(t_al *al);
void				mouse_press(t_al *al);
void				mouse_func(t_al *al);

double				power_to_run(t_al *al);
void				jump(t_al *al);

void				refresh(t_al *al);
void				yeet(t_al *al);

/*
** status functions
*/

void				editor(t_al *al);
void				menu(t_al *al);
void				game(t_al *al);
void				render(t_al *al);

/*
** hms parser
*/

int					check_links(t_sector *sec, unsigned nb_sec);
int					parse_pixels(t_tex *tex, int fd);
int					parse_texture(t_tex *tex, int fd);
int					parse_textures(t_al *al, int fd);
int					parse_sector(t_sector *sec, int fd);
int					parse_sectors(t_al *al, int fd);
int					parse_wall(t_walls *wall, int fd);
int					parse_walls(t_sector *sec, int fd);

#endif