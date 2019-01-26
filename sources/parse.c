/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 18:15:19 by ppetitea          #+#    #+#             */
/*   Updated: 2019/01/26 19:05:22 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	line_to_grid(t_point *g, char *l, int x, int z)
{
	int	j;

	j = 0;
	while (++j <= x)
	{
		g->x = (j) * MOVE_T;
		g->y = ft_atoi(l);
		g->z = (z) * MOVE_T;
		while (*l && (!ft_is_number(l[0]) || !ft_is_space(l[1])))
			l++;
		if (*l)
			l++;
		g++;
	}
}

int		ft_grid_cpy(t_point *cpy, t_point *grid, int x, int z)
{
	int		i;

	i = -1;
	if (!z)
		return (1);
	while (++i <= x * z)
		cpy[i] = grid[i];
	return (i);
}

int		check_line(t_param *p, int word_count, t_point *grid, char *line)
{
	if (!p->x)
	{
		free(line);
		if (grid)
			free(grid);
		return (!manage_error(p, 2,
			"detect empty line --> please enter a valid map\n"));
	}
	if (word_count && p->x != word_count)
	{
		free(line);
		if (grid)
			free(grid);
		return (!manage_error(p, 2,
			"detect invalid line --> please enter a valid map\n"));
	}
	return (0);
}

int		parse(t_param *p, t_point *grid, char *line, int word_count)
{
	t_point *tmp;
	int		indice;

	p->z = 0;
	while (get_next_line(p->fd, &line) > 0)
	{
		word_count = !grid ? 0 : p->x;
		p->x = ft_count_numbers(line);
		if (check_line(p, word_count, grid, line))
			return (!manage_error(p, 0, "check_line() --> parsing error\n"));
		if (!(tmp = malloc(sizeof(t_point) * (p->x * (p->z + 1) + 1))))
			return (!manage_error(p, 2, "malloc() --> malloc error\n"));
		indice = ft_grid_cpy(tmp, grid, p->x, p->z);
		free(grid);
		line_to_grid(&(tmp[indice]), line, p->x, p->z + 1);
		grid = tmp;
		p->z++;
		free(line);
	}
	free(line);
	grid[0].x = p->x;
	grid[0].z = p->z;
	p->map = grid;
	return (0);
}
