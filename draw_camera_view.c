/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_camera_view.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:23:04 by jebouche          #+#    #+#             */
/*   Updated: 2023/01/30 14:46:43 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_camera_view(t_fdf_data *fdf)
{
	int	i;
	int	j;
	t_vector3 *temp_1;
	t_vector3 *temp_2;

	i = 0;

	while (i < fdf->map_size[1])
	{
		j = 0;
		while (j < fdf->map_size[0])
		{
			temp_1 = get_camera_view(fdf, i, j);
			if (j + 1 < fdf->map_size[0])
			{
				temp_2 = get_camera_view(fdf, i, j + 1);
				draw_line(temp_1, temp_2, 0xFFFFF, fdf);
			}
			if (temp_2)
			{
				free(temp_2);
				temp_2 = NULL;
			}

			if (i + 1 < fdf->map_size[1])
			{
				temp_2 = get_camera_view(fdf, i + 1, j);
				draw_line(temp_1, temp_2, 0xFFFFF, fdf);
			}
			free(temp_1);
			if (temp_2)
			{
				free(temp_2);
				temp_2 = NULL;
			}
			j++;
		}
		i++;
	}
}