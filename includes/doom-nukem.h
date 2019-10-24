/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:24:16 by becaraya          #+#    #+#             */
/*   Updated: 2019/10/24 16:27:16 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <fcntl.h>
# include "libft.h"
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include "SDL.h"
# include "SDL_ttf.h"

# define WIN_TITLE "100% totally mario sunshine virus free i swear"
# define WIN_SIZEX 1366	//1280
# define WIN_SIZEY 768	//720
# define WIN_POSX 100
# define WIN_POSY 10

# define WIN_EDIT_SIZEY 720
# define WIN_EDIT_SIZEX 720

# define MAX_WALLS_HIT	1000
# define HORIZON_LIMIT	1000

# define D_2PI	8192 // 1<13
# define D_2PIM	8191
# define D_PI	4096
# define D_PI_2	2048
# define D_PI_4	1024

# define DEFAULT_G 9.81
# define DEFAULT_FOV D_2PI * 0.20

/*
** TEX_REPEAT is horizontal repeat in m
** TEX_REPEAT_V is vertical repeat in m*(1<<16)
** TEX_REPEAT_F is floor repeat in m*(1<<16)
*/

# define TEX_REPEAT 2.0
# define TEX_REPEAT_V 131072
# define TEX_REPEAT_F 131072

# define PLAYER_CROUCH 1.10
# define PLAYER_SIZE 1.78
# define PLAYER_EYE_TOP 0.15
# define PLAYER_MASS 67
# define PLAYER_AERO_POWER 400
# define PLAYER_ANA_POWER 1950

# define LOOK_SENS 1000

# define MERROR_MESS "Malloc error\n"

# define M_2PI 6.283185307179586476925286766559005768394338798750211641949

# define WHITE 0xffffff

/*
** Pls change this to an enum
*/

/*
** ENUMS, for all status ######################################################
*/

// typedef enum		e_status_edit
// {
// 	T_SELECT,
// 	T_WALL_DRAWING,
// 	T_WALL_IDLE,
// 	T_WALL_3
// }					t_status_edit;
/*
** main status
*/

typedef enum		e_status_draw
{
	SELECT,
	DRAWING,
	FIRST_CLICK,
	RECTANGLE_SELECT,
	RECTANGLE_DRAW
}					t_status_draw;

typedef enum		e_stat_wall
{
	SIMPLE,
	RECT
}					t_stat_wall;

/*
** TYPEDEF ####################################################################
*/

typedef	unsigned int	t_angle;

/*
** STRUCTURES #################################################################
*/

/*
** .hms parser and the main game data
*/

typedef struct		s_walls
{
	double			x1;
	double			y1;
	double			x2;
	double			y2;
	unsigned short	wall_tex;
	unsigned short	top_tex;
	unsigned short	bot_tex;
	unsigned short	is_cross;
	unsigned int	sec_lnk;
}					t_walls;

/*
**	fl:floor ce:ceiling hei:height tex:texture index
*/

typedef struct		s_sector
{
	double			fl_hei;
	double			ce_hei;
	unsigned short	fl_tex;
	unsigned short	ce_tex;
	unsigned int	nb_wal;
	t_walls			*walls;
}					t_sector;

typedef struct		s_tex
{
	unsigned int	size_x;
	unsigned int	size_y;
	unsigned int	*pix;
}					t_tex;

/*
** key currently pressed
*/

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
	t_stat_wall		type;
	struct s_wall	*next;
}					t_wall;

typedef struct		s_edit
{
	t_status_draw		stat;
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
** raycast hit descripting struct to add info missing from t_walls
** wall_length is length in m    
*/

typedef struct		s_rc_hit
{
	double		hitdst;
	unsigned	hit_texx;
	double		wall_length;
	unsigned	fl_tex;
	double		fl_hei;
	unsigned	ce_tex;
	double		ce_hei;
	t_walls		wall;
}					t_rc_hit;

/*
** raycast ray descripting func to add info missing from t_walls
** xfact and yfact are 16 bits sin and cos of anglem for floorcasting
*/

typedef struct		s_rc_ray
{
	t_angle		angle;
	int			xfact;
	int			yfact;
	int			nb_hits;
	t_rc_hit	hits[MAX_WALLS_HIT];
}					t_rc_ray;

/*
** Player info struct
** Velocities are in m/s, positions are in m, mass is in kg and power is in watt
** csec: index of current sector, must be updated if crossing sectors
** horizon: height of the horizon in pixels, indicates if lookup or down
** eyez: eye position on z
*/

typedef struct		s_player
{
	unsigned	csec;
	double		posx;
	double		posy;
	double		posz;
	double		velx;
	double		vely;
	double		velz;
	double		gd_vel;

	double		size;
	double		eyez;
	double		mass;
	double		power;
	double		power_mult;

	t_angle		dir;
	int			horizon;
	unsigned	on_ground:1;
	unsigned	alive:1;
}					t_player;

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
	unsigned		*pix;
	SDL_Surface		*sdlsurf;

	SDL_Window		*win_;
	SDL_Texture		*tex_;
	SDL_Renderer	*ren_;
	unsigned int	*pix_;
	SDL_Surface		*surf_;

	unsigned		ttf_st:1;
	TTF_Font		*font;
	SDL_Color		color;

	unsigned int	nb_sec;
	t_sector		*sec;
	t_sector		*rotsec;
	unsigned short	nb_tex;
	t_tex			*tex;

	t_player		play;
	double			g;
	t_angle			fov;
	int				stretch;

	unsigned int	fps;
	long			last_time;
	long			curr_time;
	long			tgt_time;
	int				dtime;

	t_edit			edit;

	t_keys			k;
	SDL_Event		ev;
	t_mouse			m;

	t_sector		*sec_edit;
	t_wall			*wall;
	int				c_wall;

	double			sin[D_2PI];
	double			cos[D_2PI];
	//double			tan[D_2PI];


	char			v0id[32];
}					t_al;

/*
** Prototypes #################################################################
*/

unsigned int		*parse_tex(t_al *al, char *name, int w, int h);
int					hms_parser(t_al *al, char *str);
int					pr_err(char *str);

void				init(t_al *al, char *str);
void				main_loop(t_al *al);

void				key_func(t_al *al);
void				mouse_press(t_al *al);
void				mouse_press_edit(t_al *al);
void				mouse_mv(t_al *al);
void				mouse_weel(t_al *al);

double				power_to_run(t_al *al);
void				jump(t_al *al);

t_angle				add_angle(t_angle a1, t_angle a2);
t_angle				sub_angle(t_angle a1, t_angle a2);

void				column(t_al *al, int x, t_rc_ray *ray);

void				refresh(t_al *al);
void				yeet(t_al *al);

/*
** hms parser
*/

int					check_links(t_sector *sec, unsigned nb_sec);
int					parse_pixels(t_tex *tex, int fd);
int					parse_texture(t_tex *tex, int fd);
int					parse_textures(t_al *al, int fd);
int					parse_sectors(t_al *al, int fd);

/*
** status functions
*/

void				editor(t_al *al);
void				menu(t_al *al);
void				game(t_al *al);
void				render(t_al *al);

#endif