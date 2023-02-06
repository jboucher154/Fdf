/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_camera_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:23:04 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/06 16:31:16 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_points_and_draw(t_fdf_data *fdf, int i, int j)
{
	t_vector3	*temp_1;
	t_vector3	*temp_2;

	temp_1 = get_camera_view(fdf, i, j);
	temp_2 = NULL;
	if (j + 1 < fdf->map_size[0])
	{
		temp_2 = get_camera_view(fdf, i, j + 1);
		draw_line(temp_1, temp_2, fdf);
		free(temp_2);
	}
	if (i + 1 < fdf->map_size[1])
	{
		temp_2 = get_camera_view(fdf, i + 1, j);
		draw_line(temp_1, temp_2, fdf);
		free(temp_2);
	}
	free(temp_1);
}

void	draw_camera_view(t_fdf_data *fdf)
{
	int			i;
	int			j;

	i = 0;
	while (i < fdf->map_size[1])
	{
		j = 0;
		while (j < fdf->map_size[0])
		{
			get_points_and_draw(fdf, i, j);
			j++;
		}
		i++;
	}
}

void	redraw(t_fdf_data *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img1->img);
	free(fdf->img1);
	get_new_image(fdf);
	if (!fdf->img1)
		mlx_close(fdf, 1, "Image allocation failed");
	fdf->img1->addr = mlx_get_data_addr(fdf->img1->img, \
	&fdf->img1->bits_per_pixel, &fdf->img1->line_length, \
	&fdf->img1->endian);
	draw_camera_view(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img1->img, 0, 0);
	fdf->dirty = 0;
}
