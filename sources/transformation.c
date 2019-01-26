/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 19:07:27 by ppetitea          #+#    #+#             */
/*   Updated: 2019/01/26 19:07:36 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotation_x(t_point *new, t_point p, t_move m, t_pointf r)
{
	new->x = p.x;
	new->y = cos(r.x) * (float)(m.ty * p.y) - sin(r.x) * (float)p.z;
	new->z = sin(r.x) * (float)(m.ty * p.y) + cos(r.x) * (float)p.z;
}

void	rotation_y(t_point *new, t_point p, t_pointf r)
{
	new->x = cos(r.y) * (float)p.x + sin(r.y) * (float)p.z;
	new->y = p.y;
	new->z = -sin(r.y) * (float)p.x + cos(r.y) * (float)p.z;
}

void	rotation_z(t_point *new, t_point p, t_pointf r)
{
	new->x = cos(r.z) * (float)p.x - sin(r.z) * (float)p.y;
	new->y = sin(r.z) * (float)p.x + cos(r.z) * (float)p.y;
	new->z = p.z;
}

void	translation(t_point *new, t_move m)
{
	new->x += m.tx;
	new->y += m.distance;
	new->z += m.tz;
}

void	scale(t_point *new, t_move m)
{
	new->x *= m.scale;
	new->y *= m.scale;
	new->z *= m.scale;
}
