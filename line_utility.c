/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:35:27 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/07 13:16:59 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_temps(t_vector3 *one, t_vector3 *two, t_vector3 *first, \
		t_vector3 *second)
{
	if (first->x > second->x)
	{
		one->x = second->x;
		one->y = second->y;
		one->color = second->color;
		two->x = first->x;
		two->y = first->y;
		two->color = first->color;
	}
	else
	{
		one->x = first->x;
		one->y = first->y;
		one->color = first->color;
		two->x = second->x;
		two->y = second->y;
		two->color = second->color;
	}
}

void	my_mlx_pixel_put(t_img_data *data, t_vector3 *pt, int color)
{
	char	*dst;

	if (pt->x >= WIN_WIDTH || pt->x < 0 || pt->y >= WIN_HEIGHT || pt->y < 0)
		return ;
	dst = data->addr + (pt->y * data->line_length + pt->x * \
	(data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	set_line_color(t_vector3 *first, t_vector3 *second)
{
	if (first->color > 0xFFA500)
		return (first->color);
	else if (first->color < 0xFFA500)
		return (first->color);
	else
		return (second->color);
}

void	draw_vertical(t_vector3 *first, t_vector3 *second, int color, \
		t_fdf_data *fdf)
{
	t_vector3	temp;

	if (first->y >= second->y)
	{
		temp.x = second->x;
		temp.y = second->y;
		while (temp.y <= first->y)
		{
			my_mlx_pixel_put(fdf->img1, &temp, color);
			temp.y++;
		}
	}
	else
	{
		temp.x = first->x;
		temp.y = first->y;
		while (temp.y <= second->y)
		{
			my_mlx_pixel_put(fdf->img1, &temp, color);
			temp.y++;
		}
	}
}
