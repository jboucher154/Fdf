/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:29:53 by jebouche          #+#    #+#             */
/*   Updated: 2023/01/30 16:22:55 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "ft_printf.h"


void	set_temps(t_vector3 *one, t_vector3 *two, t_vector3 *first, t_vector3 *second)
{
	one->x = first->x;
	one->y = first->y;
	two->x = second->x;
	two->y = second->y;
}

void	bresneham_pos_grad(t_vector3 *first, t_vector3 *second, int color, t_fdf_data *fdf)
{
	t_vector3	deltas;
	t_vector3	one;
	t_vector3	two;
	int			decision;

	set_temps(&one, &two, first, second);
	deltas.x = two.x - one.x;
	deltas.y = two.y - one.y;
	decision = 2 * deltas.y - deltas.x;
	while (one.x <= two.x)
	{
		my_mlx_pixel_put(fdf->img1, &one, color);
		if (decision >= 0)
		{
			one.y += 1;
			decision = decision + 2 * deltas.y - 2 * deltas.x;
		}
		else
		{
			decision = decision + 2 * deltas.y;
		}
		one.x += 1;
	}
}

void	bresneham_pos_steep(t_vector3 *first, t_vector3 *second, int color, t_fdf_data *fdf)
{
	t_vector3	deltas;
	t_vector3	one;
	t_vector3	two;
	int			decision;

	set_temps(&one, &two, first, second);
	deltas.x = two.x - one.x;
	deltas.y = two.y - one.y;
	decision = 2 * deltas.y - deltas.x;
	while (one.y <= two.y)
	{
		my_mlx_pixel_put(fdf->img1, &one, color);
		if (decision >= 0 && first->x != second->x)
		{
			one.x += 1;
			decision = decision + 2 * deltas.x - 2 * deltas.y;
		}
		else
		{
			decision = decision + 2 * deltas.x;
		}
		one.y += 1;
	}
}

void	bresneham_neg_grad(t_vector3 *first, t_vector3 *second, int color, t_fdf_data *fdf)
{
	t_vector3	deltas;
	int			decision;
	t_vector3	one;
	t_vector3	two;

	set_temps(&one, &two, first, second);
	deltas.x = two.x - one.x;
	deltas.y = two.y - one.y;
	decision = 2 * deltas.y + deltas.x;
	while (one.x <= two.x) //does this need to be >
	{
		my_mlx_pixel_put(fdf->img1, &one, color);
		if (decision >= 0)
		{
			one.y -= 1;
			decision = decision - 2 * (deltas.y + deltas.x);
		}
		else
		{
			decision = decision - (2 * deltas.y);
		}
		one.x += 1;
	}
}

void	bresneham_neg_steep(t_vector3 *first, t_vector3 *second, int color, t_fdf_data *fdf)
{
	t_vector3	deltas;
	int			decision;
	t_vector3	one;
	t_vector3	two;

	set_temps(&one, &two, first, second);
	deltas.x = two.x - one.x;
	deltas.y = two.y - one.y;
	decision = 2 * deltas.x + deltas.y;
	while (one.y >= two.y)
	{
		my_mlx_pixel_put(fdf->img1, &one, color);
		if (decision >= 0)
		{
			one.x += 1;
			decision = decision - 2 * deltas.x + 2 * deltas.y;
		}
		else
		{
			decision = decision - 2 * deltas.x;
		}
		one.y -= 1;
	}
}

void	draw_horizontal(t_vector3 *first, t_vector3 *second, int color, t_fdf_data *fdf)
{
	t_vector3	temp;

	if (first->x > second->x)
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

void	draw_line(t_vector3 *first, t_vector3 *second, int color, t_fdf_data *fdf)
{
	// t_vector3	deltas;
	double	delta_x;
	double	delta_y;

	// deltas.x = second->x - first->x;
	// deltas.y = second->y - first->y;
	delta_x = second->x - first->x;
	delta_y = second->y - first->y;
	if (second->y == first->y)
		draw_horizontal(first, second, color, fdf);
	else if (delta_x != 0 && delta_y / delta_x < 0) // first->x > second->x
	{
		if (delta_y / delta_x < -1) //check this condition
			bresneham_neg_steep(first, second, color, fdf);
		else
			bresneham_neg_grad(first, second, color, fdf);
	}
	else
	{
		if (delta_x == 0 || delta_y / delta_x > 1) //added x=0 to avoid divide by zero
			bresneham_pos_steep(first, second, color, fdf);
		else
			bresneham_pos_grad(first, second, color, fdf);	
	}
}
