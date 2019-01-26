/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 21:29:24 by ppetitea          #+#    #+#             */
/*   Updated: 2019/01/26 19:29:03 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# include <math.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include "mlx.h"
# include "libft.h"
# include "mlx_key.h"

# define SIZE 0
# define MOVE_T 50
# define MOVE_A 5
# define PI 3.14159265

typedef struct			s_pointf
{
	float				x;
	float				y;
	float				z;
}						t_pointf;

typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
}						t_point;

typedef struct			s_move
{
	int					perspective;
	float				distance;
	float				tx;
	float				ty;
	float				tz;
	float				tix;
	float				tiz;
	float				rotx;
	float				roty;
	float				rotz;
	float				scale;
	t_point				center;
}						t_move;

typedef struct			s_param
{
	int					x;
	int					z;
	int					fd;
	int					key;
	int					press;
	void				*init;
	void				*window;
	void				*img;
	int					xsize;
	int					ysize;
	int					*indices;
	int					*pixels;
	t_point				*map;
	t_point				*map_copy;
	t_move				move;
}						t_param;

t_point					move_point(t_point p, t_move m);
int						manage_input(void *param);
void					draw_map(t_param *p, t_point *map);
int						parse(t_param *p, t_point *grid, char *line,
	int word_count);
int						copy_map(t_param *p, t_point *map);
void					move_map(t_point *map_copy, t_move move, t_point *map);
void					bresenham(t_param *param, t_point *p);
void					free_and_exit(t_param *p);
void					*manage_error(t_param *p, int code,
	const char *message);
void					rotation_x(t_point *new, t_point p, t_move m,
	t_pointf r);
void					rotation_y(t_point *new, t_point p, t_pointf r);
void					rotation_z(t_point *new, t_point p, t_pointf r);
void					translation(t_point *new, t_move m);
void					scale(t_point *new, t_move m);
int						press_callback(int key, void *param);
int						release_callback(int key, void *param);

#endif
