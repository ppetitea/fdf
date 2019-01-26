/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:57:08 by ppetitea          #+#    #+#             */
/*   Updated: 2019/01/26 19:26:07 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	initialise_first_move(t_param *p)
{
	p->move.perspective = 0;
	p->move.distance = 0;
	p->move.tix = (p->xsize - (p->map->x + 1) * MOVE_T) * 0.5;
	p->move.tiz = (p->ysize - (p->map->z + 1) * MOVE_T) * 0.5;
	p->move.center.x = (p->map->x + 1) * (0.5 * MOVE_T) + p->move.tix;
	p->move.center.z = (p->map->z + 1) * (0.5 * MOVE_T) + p->move.tiz;
	p->move.tx = 0;
	p->move.ty = 1;
	p->move.tz = 0;
	p->move.rotx = 0;
	p->move.roty = 0;
	p->move.rotz = 0;
	p->move.scale = 1;
	while (p->xsize < p->map->x * MOVE_T * p->move.scale)
		p->move.scale *= 0.75;
	while (p->ysize < p->map->z * MOVE_T * p->move.scale)
		p->move.scale *= 0.75;
}

int		check_inputs(t_param *p, int ac, char **av)
{
	if (ac == 2 && (p->fd = open(av[1], O_RDONLY)) > 2
		&& read(p->fd, NULL, 0) == 0)
		return (1);
	else
	{
		ft_putstr("usage : fdf [map]\n");
		return (0);
	}
}

int		fill_param(t_param *p)
{
	int	t;
	int	x;
	int	y;

	x = 1600;
	y = 900;
	p->xsize = x;
	p->ysize = y;
	if (!(p->init = mlx_init()))
		return (!manage_error(p, 0, "mlx_init() --> error\n"));
	if (!(p->window = mlx_new_window(p->init, x, y, "fract'ol")))
		return (!manage_error(p, 0, "mlx_new_window() --> error\n"));
	if (!(p->img = mlx_new_image(p->init, x, y)))
		return (!manage_error(p, 1, "mlx_new_image() --> error\n"));
	if (!(p->pixels = (int*)mlx_get_data_addr(p->img, &t, &t, &t)))
		return (!manage_error(p, 1, "mlx_get_data() --> error\n"));
	return (0);
}

int		main(int ac, char **av)
{
	t_param p;

	if (check_inputs(&p, ac, av))
	{
		if (fill_param(&p))
			return (!manage_error(&p, 0, "fill_param() --> error\n"));
		if (parse(&p, NULL, NULL, 0))
			return (!manage_error(&p, 0, "parse() --> error\n"));
		initialise_first_move(&p);
		if (copy_map(&p, p.map))
			return (!manage_error(&p, 0, "copy_map() --> error\n"));
		move_map(p.map_copy, p.move, p.map);
		draw_map(&p, p.map);
		mlx_hook(p.window, 2, 1L << 0, press_callback, (void*)&p);
		mlx_hook(p.window, 3, 1L << 1, release_callback, (void*)&p);
		mlx_loop_hook(p.init, manage_input, (void*)&p);
		mlx_loop(p.init);
	}
	return (0);
}
