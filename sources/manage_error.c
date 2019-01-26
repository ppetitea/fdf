/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppetitea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 16:31:50 by ppetitea          #+#    #+#             */
/*   Updated: 2019/01/26 18:43:51 by ppetitea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*manage_error(t_param *p, int code, const char *message)
{
	ft_putstr(message);
	if (code > 23)
		free(p->map_copy);
	if (code > 2)
		free(p->map);
	if (code > 1)
		mlx_destroy_image(p->init, p->img);
	if (code > 0)
		mlx_destroy_window(p->init, p->window);
	return (NULL);
}
