/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:18:07 by ppetitea          #+#    #+#             */
/*   Updated: 2019/01/26 19:06:08 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		copy_map(t_param *p, t_point *map)
{
	t_point	*map_copy;
	int		i;

	if (!(map_copy = malloc(sizeof(t_point) * (map->x * map->z + 1))))
		return (!manage_error(p, 3, "malloc() --> malloc error\n"));
	i = 0;
	while (i < map->x * map->z + 1)
	{
		map_copy[i] = map[i];
		map_copy[i].x += p->move.tix;
		map_copy[i].z += p->move.tiz;
		i++;
	}
	p->map_copy = map_copy;
	return (0);
}
