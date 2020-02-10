/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 12:24:16 by becaraya          #+#    #+#             */
/*   Updated: 2020/02/06 14:55:42 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <fcntl.h>
# include "libft.h"
# include <stdio.h>
# include <math.h>
# include <limits.h>
# include <sys/time.h>
# include <SDL2/SDL.h>
# include <SDL2_ttf/SDL_ttf.h>
# include <SDL2_image/SDL_image.h>
# include <SDL2_mixer/SDL_mixer.h>

# define WIN_TITLE "100% really slenderman absolutely virus free i swear"
# define WIN_SIZEX 1280
# define WIN_SIZEY 720
# define WIN_POSX 100
# define WIN_POSY 10
# define GRO 1.1

# define WIN_EDIT_SIZEX	768
# define WIN_EDIT_SIZEY	720

# define MAX_HITS	1000
# define HORIZON_LIMIT	1000
# define F19 1073741934

# define D_2PI	8192
# define D_2PIM	8191
# define D_PI	4096
# define D_PI_2	2048
# define D_PI_4	1024

# define DEFAULT_G 9.81
# define DEFAULT_FOV 1.6

# define SPRITE_W 512
# define SPRITE_H 512

# define MAX_X 100000

/*
** TEX_REPEAT is horizontal repeat in m
** TEX_REPEAT_V is vertical repeat in m*(1<<16)
*/

# define TEX_REPEAT 2.0
# define TEX_REPEAT_V 131072

/*
** now this one is very strange. REPEAT_F is repeat distance * 0x10000 - 1
** and it is used as a mask so the -1 is important
** REPEAT_F_DIV is log2 of REPEAT_F + 1, and to emulate a division with a
** bit shift
*/

# define TEX_REPEAT_F 131071
# define TEX_REPEAT_F_DIV 17

# define PLAYER_CROUCH 1.10
# define PLAYER_SIZE 1.78
# define PLAYER_EYE_TOP 0.15
# define PLAYER_MASS 67
# define PLAYER_AERO_POWER 400
# define PLAYER_ANA_POWER 950

# define LOOK_SENS 1000

# define MERROR_MESS "Malloc error\n"

# define M_2PI 6.283185307179586476925286766559005768394338798750211641949

# define BLACK			0x0
# define WHITE			0x80ffffff
# define WHITE_L		0xCDCDCD
# define LIGHT_GREY		0xb0b0b0
# define DARK_GREY		0x606060
# define RED			0xff0000
# define BLUE			0x0000ff
# define DARK_RED		0xa50029
# define YELLOW			0xffff00
# define DARK_YELLOW	0xdec111
# define GREEN			0x00ff00
# define DARK_GREEN		0x108010

# define BACK_GROUND LIGHT_GREY
# define TEXT_EDITOR BLACK

# define TEX_SIZE_MENU 100

/*
** ENUMS, for all status ######################################################
*/

/*
** main status
*/

typedef enum		e_status
{
	MENU,
	GAME,
	DEAD,
	PAUSE,
	EDIT,
	WON
}					t_status;

typedef enum		e_status_ed
{
	SELECT,
	DRAWING,
	SET_SPAWN,
	SET_END,
	SET_BAD_PIG,
	SET_FLO_TEXT,
	SET_FLO_HEI,
	SET_CEL_TEXT,
	SET_CEL_HEI,
	SET_WALL_TEXT,
	LINK_MOD,
	EDIT_WALL,
	EDIT_SECT,
	SET_PLAYER,
	LIFE,
	POW,
	WEAPON,
	SIZE,
	MASS,
	GRAVITY,
	IS_DOOR
}					t_status_ed;

/*
** TYPEDEF ####################################################################
*/

typedef	unsigned	t_angle;

/*
** STRUCTURES #################################################################
*/

typedef struct		s_floorcast
{
	long			posx;
	long			posy;
	long			dstx;
	long			dsty;
	long			dst;
	int				hor;
	int				indst;
}					t_floorcast;

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
	unsigned		is_cross:1;
	unsigned int	sec_lnk;
	struct s_walls	*next;
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
	struct s_sector	*next;
}					t_sector;

typedef struct		s_tex
{
	unsigned int	size_x;
	unsigned int	size_y;
	unsigned int	*pix;
}					t_tex;

typedef struct		s_tex_or
{
	unsigned int	**pix;
}					t_tex_or;

typedef struct		s_tex_group
{
	unsigned int	size_x;
	unsigned int	size_y;
	unsigned int	nb_tex;
	t_tex_or		or[9];
}					t_tex_group;

/*
** key currently pressed
*/

typedef struct		s_keys
{
	unsigned		w:1;
	unsigned		a:1;
	unsigned		s:1;
	unsigned		d:1;
	unsigned		t:1;
	unsigned		m:1;
	unsigned		lbrack:1;
	unsigned		rbrack:1;
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

/*
** typedef struct		s_icon
** {
** 	unsigned int	*chest;
** 	unsigned int	*click;
** 	unsigned int	*path;
** 	unsigned int	*portal;
** 	unsigned int	*wall;
** }					t_icon;
*/

typedef struct		s_point
{
	int				x;
	int				y;
	int				color;
}					t_point;

typedef struct		s_doint
{
	double			x;
	double			y;
	int				color;
}					t_doint;

typedef struct		s_oint
{
	t_doint			d;
	t_point			p;
}					t_oint;

/*
** typedef struct		s_wall
** {
**	int				x1;
**	int				y1;
**	int				x2;
**	int				y2;
**	t_stat_wall		type;
**	struct s_wall	*prev;
**	struct s_wall	*next;
**}					t_wall;
*/

typedef struct		s_edit
{
	t_status_ed		stat;
	int				zoom;
	int				sect_end;
	double			spawnz;
	t_doint			set_spawn;
	unsigned int	index_wall;
	unsigned int	index_sect;
}					t_edit;

/*
** Player info struct
** Velocities are in m/s, positions are in m, mass is in kg and power is in watt
** csec: index of current sector, must be updated if crossing sectors
** horizon: height of the horizon in pixels, indicates if lookup or down
** eyez: eye position on z
*/

typedef struct		s_sprite
{
	int				id;
	int				w;
	int				h;
	int				x;
	int				y;
	int				angle;
	double			dist;
	unsigned int	*tex;
	struct s_sprite	*next;
}					t_sprite;

typedef struct		s_player
{
	unsigned		csec;
	double			posx;
	double			posy;
	double			posz;
	double			velx;
	double			vely;
	double			velz;
	double			gd_vel;
	unsigned		fly:1;
	unsigned		on_ground:1;
	int				alive;
	t_angle			dir;

	double			size;
	double			eyez;
	double			mass;
	double			power;
	double			power_mult;
	unsigned		won:1;

	unsigned		dmg;
	int				horizon;
}					t_player;

/*
** i think some var are usless on entity.
*/

/*
** perhaps.
*/

typedef struct		s_mob
{
	unsigned		csec;
	double			posx;
	double			posy;
	double			posz;
	double			velx;
	double			vely;
	double			velz;
	double			gd_vel;
	unsigned		on_ground:1;
	unsigned		alive;
	t_angle			dir;
	t_angle			angle_to_player;
	unsigned		hit;
	unsigned		index;
	unsigned		fly:1;
	double			size;
	double			width;
	double			mass;
	double			power;
	unsigned		anim;
	struct s_mob	*next;
}					t_mob;

typedef union		u_entity
{
	t_player		pl;
	t_mob			mob;
}					t_entity;

/*
** raycast hit limits descripting struct
** first set of limits are horizon corrected lims, while the 2nd set is
** horizon corrected and screen size capped
** mb: mental breakdown. I have given up on remaining sane
*/

typedef struct		s_rc_lim
{
	int				toplim;
	int				topwall;
	int				topmid;
	int				botmid;
	int				botwall;
	int				botlim;

	int				sc_toplim;
	int				sc_topwall;
	int				sc_topmid;
	int				sc_botmid;
	int				sc_botwall;
	int				sc_botlim;

	int				mb_botlim;
	int				mb_toplim;
}					t_rc_lim;

/*
** raycast hit descripting struct to add info missing from t_walls
** wall_length is length in m
*/

typedef struct		s_rc_hit
{
	double			hitdst;
	unsigned		hit_texx;
	double			wall_length;
	unsigned		botwall_he;
	unsigned		topwall_he;
	unsigned		wall_he;
	unsigned		fl_tex;
	double			fl_hei;
	unsigned		ce_tex;
	double			ce_hei;
	t_walls			wall;
	t_mob			ent;
	t_tex			tex;
	t_rc_lim		lim;
	unsigned		transparent:1;
	unsigned		is_entity:1;
}					t_rc_hit;

/*
** raycast ray descripting func to add info missing from t_walls
** xfact and yfact are 16 bits sin and cos of angle for floorcasting
** min is used in test_hit
*/

typedef struct		s_rc_ray
{
	int				x;
	t_angle			angle;
	int				xfact;
	int				yfact;
	int				nb_hits;
	t_rc_hit		hits[MAX_HITS];

	double			min;
	double			minent;
}					t_rc_ray;

typedef struct		s_text
{
	char			*str;
	SDL_Color		clr;
	SDL_Rect		*where;
}					t_text;

typedef struct		s_text_list
{
	t_text			t;
	t_text			gen_map;
	t_text			sect_index;
	t_text			wall_index;
	t_text			settings;
	t_text			wall_para;
	t_text			sect_para;
	t_text			wall;
	t_text			sector;
	t_text			tools;
	t_text			cancel;

	t_text			wall_tex;

	t_text			fl_hei;
	t_text			ce_hei;
	t_text			fl_hei_num;
	t_text			ce_hei_num;
	t_text			fl_tex;
	t_text			ce_tex;
	t_text			set_player;
	t_text			life;
	t_text			power;
	t_text			weapon;
	t_text			size;
	t_text			mass;

	t_text			set_spawn;
	t_text			set_end;
	t_text			set_bad_pig;
	t_text			draw;
	t_text			del_sect;

	t_text			player_value;

	t_text			dif_ez;
	t_text			dif_ha;

	t_text			gravity;
	t_text			g_num;
	t_text			reset_map;
	t_text			reset_player;

	t_text			is_door;

	t_text			link;
}					t_text_list;

/*
** Main structure #############################################################
** h = heart f = flingue
*/

typedef struct		s_al
{
	unsigned		end;
	int				hard;
	t_status		status;
	char			*map_write_name;
	void			(*stat_fnc[6])(struct s_al *);

	SDL_Window		*sdlwin;
	SDL_Surface		*sdlsurf;
	unsigned		*pix;

	unsigned		pix_dead[WIN_SIZEX * WIN_SIZEY];
	t_tex			you_died;
	t_tex			you_win;

	SDL_Window		*win_ed;
	SDL_Surface		*surf_ed;
	unsigned		*pix_ed;

	unsigned		ttf_st:1;
	TTF_Font		*font;
	t_text_list		text;
	SDL_Color		color;

	unsigned int	nb_sec;
	unsigned int	sp_key_sec;
	t_sector		*sec;
	t_sector		*rotsec;
	t_sector		*tmp_sec;
	unsigned short	nb_tex;
	t_tex			*tex;
	unsigned short	nb_texgp;
	t_tex_group		*texgp;

	t_tex			h;
	t_tex			f;
	t_tex			weapon[7];
	t_tex			mob_death[8];

	unsigned short	nb_ent;
	t_mob			*ent;
	t_mob			*rotent;
	t_mob			*tmp_ent;
	t_mob			*tmp_ent2;

	t_player		play;
	double			g;
	double			fov;

	int				stretch;
	int				wall_scale;

	unsigned int	fps;
	long			last_time;
	long			curr_time;
	long			tgt_time;
	unsigned int	dtime;

	unsigned short	anim;
	unsigned int	fire_anim;

	t_edit			edit;
	int				tex_choice;

	int				diff:1;

	t_keys			k;
	SDL_Event		ev;
	t_mouse			m;

	t_sector		*sect;

	double			sin[D_2PI];
	double			cos[D_2PI];

	t_sprite		*sprite;

	char			v0id[32];

	t_point			end_sect;
	int				door;
}					t_al;

/*
** Prototypes #################################################################
*/

unsigned int		*parse_tex(t_al *al, char *name, int w, int h);
int					pr_err(char *str);

void				init(t_al *al, char *str, int ed);
void				main_loop(t_al *al);
void				pix_to_pix(unsigned *src, unsigned *dst, double alpha);

void				key_func(t_al *al);
void				mouse_press(t_al *al);
void				mouse_press_edit(t_al *al);
void				mouse_mv(t_al *al);
void				mouse_weel(t_al *al);

double				power_to_run(t_al *al);
void				jump(t_al *al);

t_angle				add_angle(t_angle a1, t_angle a2);
t_angle				sub_angle(t_angle a1, t_angle a2);

void				column(t_al *al, t_rc_ray *ray);

int					skybox(t_al *al, int y, int tx);
int					tex_find(unsigned int *pix, int texx, int texy,
	t_tex *tex);
void				pimp_cross(t_al *al);
void				refresh(t_al *al);
void				cap_int(int *var, int lowcap, int highcap);

/*
** free fonction
** becaraya is dumb lololo
** he sexy tho
*/

void				free_wall(t_walls *walls);
void				ft_rectdel(SDL_Rect **re);
void				yeet(t_al *al);
void				free_text_hei_num(t_al *al);
void				get_map(t_al *al);
t_walls				*get_walls(t_al *al, unsigned int nb_sec);
t_walls				*create_walls_elem(t_al *al, unsigned int nb_sec, unsigned
	int nb_wal);
t_sector			*create_sector_elem(t_al *al, unsigned int nb_sec);
void				free_text(t_al *al);

/*
** hms parser
*/

int					hms_parser(t_al *al, char *str);
int					check_links(t_sector *sec, unsigned nb_sec);
int					parse_pixels(t_tex *tex, int fd);
int					parse_texture(t_tex *tex, int fd);
int					parse_sectors(t_al *al, int fd);
int					parse_textures(t_al *al, int fd);
int					parse_texture_groups(t_al *al, int fd);

int					bmp_to_tex(t_tex *tex, char *str, unsigned sizex, unsigned
	sizey);

/*
** hms encoder
*/

int					hms_encoder(t_al *al, char *str);
int					write_sectors(t_al *al, int fd);
int					write_textures(t_al *al, int fd);
int					write_texture_groups(t_al *al, int fd);

/*
** status functions
*/

void				editor(t_al *al);
void				menu(t_al *al);
void				game(t_al *al);
void				dead(t_al *al);
void				render(t_al *al);

/*
** sprites functions
*/
void				init_texgrp(t_al *al);
void				display_texgp(t_al *al, unsigned int *pix);

/*
** draw function
*/

void				ft_put_line(t_point a, t_point b, SDL_Surface *surf, int
	color);
void				put_rectangle(SDL_Surface *surf, t_point a, t_point b, int
	clr);
/*
** authorization too mooving function
*/

void				ft_nop(t_al *al, t_mob *e, double x, double y);
void				ft_nop_player(t_al *al, int i, double x, double y);

/*
** SDL Tools
*/

SDL_Rect			get_rect(int x, int y);
SDL_Color			add_color(int color);

/*
**	Draw Tools
*/

void				draw_triangle(t_point p, int i, SDL_Surface *surf, int
	color);
void				ft_put_line(t_point a, t_point b, SDL_Surface *surf, int
	color);
void				put_rectangle(SDL_Surface *surf, t_point a, t_point b, int
	clr);

/*
**	Draw edit Tools
*/

void				draw_sect(t_al *al, t_sector *sect);

void				draw_wall(t_al *al, t_walls *wall, int clr);

void				draw_sect_index(t_al *al, t_sector *sect,
	unsigned int i_s);
void				draw_wall_index(t_al *al, t_walls *wall, int index);

/*
** Struct Edit Tool
*/

int					check_end_sector(t_walls *wall, int x, int y);
void				check_can_add(t_al *al, t_sector *sect, t_point coo);
void				delonesect(t_sector **sect);

/*
** Generic Tools
*/

t_point				itop(int x, int y);
unsigned int		nb_wall(t_al *al);
int					inr(t_point src_a, t_point src_b, t_point cmp);
t_point				itop(int x, int y);
int					is_in_sector(t_al *al, double x, double y);
int					cocmp(SDL_Rect *p1, SDL_Rect *p2);

/*
** action of entity
*/

void				acceleration_entities(t_al *al, t_mob *mob);

/*
** Text
*/

void				init_ttf(t_al *al);
int					set_text(t_text *text, char *str, SDL_Rect coo,
	SDL_Color clr);
int					titlecmp(t_al *al, t_text text);
void				display_tex_menu(SDL_Surface *surf, t_tex tex, int i);
void				click_on_menu(t_al *al, SDL_Surface *surf);
void				tex_menu(t_al *al);
void				init_text_edit(t_al *al);
void				init_text_edit_next(t_al *al);

/*
** Event
*/

void				mouse_press_menu(t_al *al);
void				mouse_press(t_al *al);
void				mouse_mv(t_al *al);
void				mouse_weel(t_al *al);

/*
** Editor
*/

void				set_edit(t_al *al);
void				set_edit_menu_next(t_al *al);
void				set_edit_menu(t_al *al);
int					cross_wall(t_walls a, t_walls b);
void				sect_wall_menu_rectangle(t_al *al);
void				global_menu_rectangle(t_al *al);
void				set_edit_menu_next(t_al *al);
void				arrow_stat(t_al *al, SDL_MouseButtonEvent bev);
void				arrow_stat_player_minus(t_al *al);
void				arrow_stat_player_plus(t_al *al);
void				mouse_press_edit_mini_menu(t_al *al,
	SDL_MouseButtonEvent bev);
void				mouse_press_edit_setting_sector(t_al *al,
	SDL_MouseButtonEvent bev);
void				mouse_press_edit_player(t_al *al,
	SDL_MouseButtonEvent bev);

/*
** TRUC
*/

int					bmp_to_pix(unsigned **pix, char *str, unsigned sizex,
	unsigned sizey);
char				*dtoa_doom(double n);
void				add_wall(t_al *al, t_sector *sect, t_point coo);
void				add_sector(t_al *al, t_point coo);
void				init_sect(t_al *al, t_sector *sect);
void				set_coo(t_al *al, t_point bev, int who, t_walls *wall);
void				get_sec_tab(t_al *al);
void				free_sect(t_sector *sect);
void				init_sec_tex(t_al *al);
void				free_text(t_al *al);
void				display_tab(t_al *al);
void				display(t_al *al);

void				cap_int(int *var, int lowcap, int highcap);
void				hit_floor(t_al *al, t_rc_ray *ray, int hitnb);
void				hit_ceiling(t_al *al, t_rc_ray *ray, int hitnb);
void				hit_top_bot_wall(t_al *al, t_rc_ray *ray, int hitnb);
void				hit_wall(t_al *al, t_rc_ray *ray, int hitnb);
int					tex_find(unsigned int *pix, int texx, int texy,
	t_tex *tex);
int					skybox(t_al *al, int y, int tx);
void				hit_wall_heights(t_al *al, t_rc_hit *hit, t_rc_lim *lim,
	int hor);
void				hit_next_walls(t_al *al, t_rc_hit *hit, t_rc_lim *lim,
	int hor);
void				hit_linesave_ent(t_al *al, t_rc_hit *hit, t_rc_lim *lim,
int hor);
unsigned			new_wall_he(t_rc_hit *hit, t_rc_hit *nhit);

void				diplacement(t_al *al);
void				displacement(t_al *al);
void				acceleration(t_al *al);
void				deceleration(t_al *al);
t_angle				angle(t_al *al);
void				rotate(t_al *al);

void				text(t_al *al);

void				rot_sec(t_al *al, unsigned int secid, t_angle angle);
void				rot_ents(t_al *al, t_angle angle);
void				cast_sec(t_al *al, t_rc_ray *ray, unsigned secid, t_angle
	angle);
void				cast_ray(t_al *al, t_angle an, t_rc_ray *ray);

void				javoue_jabuse1(t_tex_group *tgp, unsigned i, unsigned or);
int					test_aleready_hit(t_rc_ray *ray, t_walls *owall);
int					test_hit(t_al *al, t_rc_ray *ray, t_walls *wall, t_walls
	*owall);
int					test_ent_aleready_hit(t_rc_ray *ray, t_mob *oent);
int					test_ent_hit(t_al *al, t_rc_ray *ray, t_mob *rotent, t_mob
	*oent);

void				rotate(t_al *al);
void				free_before_refresh(t_al *al);
void				add_sector(t_al *al, t_point coo);
t_angle				d_atan2(double d1, double d2);
t_angle				d_atan(double a);
void				swapd(double *d1, double *d2);
double				wall_len(t_walls *wall);
t_tex				find_ent_tex(t_al *al, t_mob *ent);
void				draw_map(t_al *al);
void				print_co(t_al *al);
int					count_wall(t_walls *walls);
void				mob_on_z(t_al *al, t_mob *e);

t_mob				*new_mob(t_al *al, SDL_MouseButtonEvent bev, unsigned i);
t_mob				*init_pig(t_al *al, t_mob *mob, t_mob *tmp, unsigned i);
void				badpig(t_al *al, SDL_MouseButtonEvent bev);
void				edit_to_game(t_al *al);
void				link_sectors(t_al *al);
void				pewpew(t_al *al);
void				set_spawn(t_al *al, SDL_MouseButtonEvent spw);
void				set_end(t_al *al, SDL_MouseButtonEvent bev);
void				convert_end(t_al *al);
void				print_text(t_al *al, t_text text, SDL_Surface *surf);
void				pig_pos(t_al *al);

unsigned			alphapix(unsigned pix, double alpha);
void				prepare_exit(t_al *al);
void				load_hud(t_al *al);
void				load_death(t_al *al);
void				init_textures(t_al *al);
void				free_tab(t_al *al);
void				load_pig(t_al *al);
void				bzerooo(void *s, size_t n);
void				init_trigo(t_al *al);
void				init_edit(t_al *al);
void				finish_write(t_al *al, int true);
int					pr_err(char *str);
void				won(t_al *al);

#endif
