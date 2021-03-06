/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 19:09:13 by ppetitea          #+#    #+#             */
/*   Updated: 2019/01/26 19:09:31 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_abs(int nb)
{
	if (nb < 0)
		nb = -nb;
	return (nb);
}

void	bresenham_dz(t_param *param, t_point *p)
{
	int	e;
	int	dx;
	int	dz;
	int	xs;
	int	zs;

	e = ft_abs(p[1].z - p[0].z);
	dz = 2 * e;
	dx = 2 * ft_abs(p[1].x - p[0].x);
	xs = p[1].x > p[0].x ? 1 : -1;
	zs = p[1].z > p[0].z ? 1 : -1;
	while (p->z != p[1].z + zs && p->z >= 0 && p->z <= param->ysize)
	{
		if (p->x > 0 && p->x < param->xsize
			&& p->z > 0 && p->z < param->ysize)
			param->pixels[p->x + p->z * param->xsize] = 0x00FFFFFF;
		e -= dx;
		if (e < 0)
		{
			p->x += xs;
			e += dz;
		}
		p->z += zs;
	}
}

void	bresenham_dx(t_param *param, t_point *p)
{
	int	e;
	int	dx;
	int	dz;
	int	xs;
	int	zs;

	e = ft_abs(p[1].x - p[0].x);
	dx = 2 * e;
	dz = 2 * ft_abs(p[1].z - p[0].z);
	xs = p[1].x > p[0].x ? 1 : -1;
	zs = p[1].z > p[0].z ? 1 : -1;
	while (p->x != p[1].x + xs && p->x >= 0 && p->x <= param->xsize)
	{
		if (p->x > 0 && p->x < param->xsize
			&& p->z > 0 && p->z < param->ysize)
			param->pixels[p->x + p->z * param->xsize] = 0x00FFFFFF;
		e -= dz;
		if (e < 0)
		{
			p->z += zs;
			e += dx;
		}
		p->x += xs;
	}
}

void	bresenham(t_param *param, t_point *p)
{
	if (ft_abs(p[1].x - p[0].x) > ft_abs(p[1].z - p[0].z))
		bresenham_dx(param, p);
	else
		bresenham_dz(param, p);
}
