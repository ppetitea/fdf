/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 19:08:17 by ppetitea          #+#    #+#             */
/*   Updated: 2019/01/26 19:09:52 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		line_belong_to_window(t_param *param, t_point *p)
{
	t_point	tmp;

	if (p[0].x >= 0 && p[0].x <= param->xsize
		&& p[0].z >= 0 && p[0].z <= param->ysize)
		return (1);
	tmp = p[0];
	p[0] = p[1];
	p[1] = tmp;
	if (p[0].x >= 0 && p[0].x <= param->xsize
		&& p[0].z >= 0 && p[0].z <= param->ysize)
		return (1);
	return (0);
}

void	draw_map(t_param *param, t_point *map)
{
	t_point	p[2];
	int		i;

	i = 0;
	while (++i < map->x * map->z + 1)
	{
		if (i % map->x)
		{
			p[0] = map[i];
			p[1] = map[i + 1];
			if (line_belong_to_window(param, p))
				bresenham(param, p);
		}
		if (i <= map->x * (map->z - 1))
		{
			p[0] = map[i];
			p[1] = map[i + map->x];
			if (line_belong_to_window(param, p))
				bresenham(param, p);
		}
	}
	mlx_put_image_to_window(param->init, param->window, param->img, 0, 0);
}
