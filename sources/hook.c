/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 19:10:04 by ppetitea          #+#    #+#             */
/*   Updated: 2019/01/26 19:11:27 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_image(t_param *p)
{
	int	i;

	i = -1;
	while (++i <= p->xsize * p->ysize)
		p->pixels[i] = 0;
}

void	ft_move(int key, t_move *m)
{
	m->perspective = key == KEY_P ? 1 : m->perspective;
	m->perspective = key == KEY_O ? 0 : m->perspective;
	m->distance += key == KEY_PAGE_DOWN ? -MOVE_T : 0;
	m->distance += key == KEY_PAGE_UP ? MOVE_T : 0;
	m->tx += (key == KEY_LEFT) ? -MOVE_T : 0;
	m->tx += (key == KEY_RIGHT) ? MOVE_T : 0;
	m->ty *= (key == KEY_PAD_1) ? 0.75 : 1;
	if (m->ty < 42)
		m->ty *= (key == KEY_PAD_3) ? 1.5 : 1;
	m->tz += (key == KEY_UP) ? -MOVE_T : 0;
	m->tz += (key == KEY_DOWN) ? MOVE_T : 0;
	m->rotz += (key == KEY_PAD_4) ? MOVE_A : 0;
	m->rotz += (key == KEY_PAD_6) ? -MOVE_A : 0;
	m->rotx += (key == KEY_PAD_8) ? MOVE_A : 0;
	m->rotx += (key == KEY_PAD_2) ? -MOVE_A : 0;
	m->roty += (key == KEY_PAD_0) ? MOVE_A : 0;
	m->roty += (key == KEY_PAD_DOT) ? -MOVE_A : 0;
	m->scale *= (key == KEY_PAD_SUB) ? 0.75 : 1;
	if (m->scale < 100)
		m->scale *= (key == KEY_PAD_ADD) ? 1.5 : 1;
}

int		manage_input(void *param)
{
	t_param	*p;

	p = (t_param*)param;
	if (p->key == KEY_ESCAPE)
	{
		manage_error(p, 4, "Exit with ESC\n");
		exit(0);
	}
	if (p->press)
	{
		ft_move(p->key, &(p->move));
		reset_image(p);
		mlx_clear_window(p->init, p->window);
		move_map(p->map_copy, p->move, p->map);
		draw_map(p, p->map);
	}
	return (0);
}
