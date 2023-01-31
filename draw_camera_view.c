/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_camera_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:23:04 by jebouche          #+#    #+#             */
/*   Updated: 2023/01/31 17:00:53 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_temp_check(t_vector3 **temp)
{
	if (*temp)
	{
		free(*temp);
		(*temp) = NULL;
	}
}

void	get_points_and_draw(t_fdf_data *fdf, int i, int j)
{
	t_vector3	*temp_1;
	t_vector3	*temp_2;

	temp_1 = get_camera_view(fdf, i, j);
	temp_2 = NULL;
	if (j + 1 < fdf->map_size[0])
	{
		temp_2 = get_camera_view(fdf, i, j + 1);
		draw_line(temp_1, temp_2, 0xFFFFF, fdf);
	}
	free_temp_check(&temp_2);
	if (i + 1 < fdf->map_size[1])
	{
		temp_2 = get_camera_view(fdf, i + 1, j);
		draw_line(temp_1, temp_2, 0xFFFFF, fdf);
	}
	free_temp_check(&temp_1);
	free_temp_check(&temp_2);
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
