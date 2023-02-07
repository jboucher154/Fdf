/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:29:53 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/07 13:16:48 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bresneham_pos_steep(t_vector3 *first, t_vector3 *second, int color, \
		t_fdf_data *fdf)
{
	t_vector3	deltas;
	t_vector3	one;
	t_vector3	two;
	int			decision;

	set_temps(&one, &two, first, second);
	deltas.x = two.x - one.x;
	deltas.y = two.y - one.y;
	decision = (2 * deltas.y) - deltas.x;
	while (one.y <= two.y)
	{
		my_mlx_pixel_put(fdf->img1, &one, color);
		if (decision > 0 && first->x != second->x)
		{
			one.x += 1;
			decision += 2 * (deltas.x - deltas.y);
		}
		else
		{
			decision += 2 * deltas.x;
		}
		one.y += 1;
	}
}

void	bresneham_neg_steep(t_vector3 *first, t_vector3 *second, int color, \
		t_fdf_data *fdf)
{
	t_vector3	deltas;
	int			decision;
	t_vector3	one;
	t_vector3	two;

	set_temps(&one, &two, first, second);
	deltas.x = two.x - one.x;
	deltas.y = (two.y - one.y);
	decision = (2 * deltas.y) - deltas.x;
	while (one.y >= two.y)
	{
		my_mlx_pixel_put(fdf->img1, &one, color);
		if (decision >= 0)
		{
			one.x += 1;
			decision += 2 * (deltas.x + deltas.y);
		}
		else
		{
			decision += 2 * deltas.x;
		}
		one.y -= 1;
	}
}

void	bresneham_grad(t_vector3 *first, t_vector3 *second, int color, \
		t_fdf_data *fdf)
{
	t_vector3	deltas;
	int			decision;
	t_vector3	one;
	t_vector3	two;
	int			slope;

	slope = 1;
	set_temps(&one, &two, first, second);
	deltas.x = two.x - one.x;
	deltas.y = two.y - one.y;
	if ((double) deltas.y / (double) deltas.x < 0)
		slope = -1;
	decision = (2 * deltas.y * slope) - deltas.x;
	while (one.x <= two.x)
	{
		my_mlx_pixel_put(fdf->img1, &one, color);
		if (decision >= 0)
		{
			one.y += slope;
			decision += 2 * ((deltas.y * slope) - deltas.x);
		}
		else
			decision += 2 * (deltas.y * slope);
		one.x += 1;
	}
}

void	draw_horizontal(t_vector3 *first, t_vector3 *second, int color, \
		t_fdf_data *fdf)
{
	t_vector3	temp;

	if (first->x >= second->x)
	{
		temp.x = second->x;
		temp.y = second->y;
		while (temp.x <= first->x)
		{
			my_mlx_pixel_put(fdf->img1, &temp, color);
			temp.x++;
		}
	}
	else
	{
		temp.x = first->x;
		temp.y = first->y;
		while (temp.x <= second->x)
		{
			my_mlx_pixel_put(fdf->img1, &temp, color);
			temp.x++;
		}
	}
}

void	draw_line(t_vector3 *first, t_vector3 *second, \
		t_fdf_data *fdf)
{
	double	delta_x;
	double	delta_y;
	int		color;

	if (((first->x > WIN_WIDTH || first->x < 0) && (first->y > WIN_HEIGHT || \
		first->y < 0)) && ((second->x > WIN_WIDTH || second->x < 0) && \
		(second->y > WIN_HEIGHT || second->y < 0)))
		return ;
	color = set_line_color(first, second);
	delta_x = second->x - first->x;
	delta_y = second->y - first->y;
	if (second->y == first->y)
		draw_horizontal(first, second, color, fdf);
	else if (second-> x == first->x)
		draw_vertical(first, second, color, fdf);
	else if (delta_y / delta_x >= -1 && delta_y / delta_x <= 1)
	{
		bresneham_grad(first, second, color, fdf);
	}
	else if (delta_x != 0 && delta_y / delta_x < 0)
		bresneham_neg_steep(first, second, color, fdf);
	else
		bresneham_pos_steep(first, second, color, fdf);
}
