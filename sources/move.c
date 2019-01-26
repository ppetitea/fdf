/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 18:15:19 by ppetitea          #+#    #+#             */
/*   Updated: 2019/01/26 19:07:04 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define RAD 0.01745329251

void	ft_fill_radiant(t_pointf *rad, t_move m)
{
	rad->x = m.rotx * RAD;
	rad->y = m.roty * RAD;
	rad->z = m.rotz * RAD;
}

t_point	perspective(t_point p)
{
	int	distance;

	distance = 1;
	if (p.y >= 1000)
		p.y = 999;
	p.x = (float)p.x / (1 - ((float)p.y * 0.001f));
	p.z = (float)p.z / (1 - ((float)p.y * 0.001f));
	return (p);
}

t_point	move_point(t_point p, t_move m)
{
	t_point		new;
	t_pointf	r;

	new.x = p.x - m.center.x;
	new.y = p.y;
	new.z = p.z - m.center.z;
	ft_fill_radiant(&r, m);
	rotation_x(&new, new, m, r);
	rotation_y(&new, new, r);
	rotation_z(&new, new, r);
	scale(&new, m);
	translation(&new, m);
	if (m.perspective)
		new = perspective(new);
	new.x += m.center.x;
	new.z += m.center.z;
	return (new);
}

void	move_map(t_point *map_copy, t_move move, t_point *map)
{
	int	i;

	i = 0;
	while (++i < map->x * map->z + 1)
		map[i] = move_point(map_copy[i], move);
}
