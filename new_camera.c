/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:48:33 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/07 13:07:02 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	initial_scale(t_fdf_data *fdf)
{
	int	w_ratio;
	int	h_ratio;

	w_ratio = WIN_WIDTH / fdf->map_size[0];
	h_ratio = WIN_HEIGHT / fdf->map_size[1];
	if (w_ratio == 0 && h_ratio == 0)
		return (2);
	if (w_ratio < h_ratio)
	{
		if (w_ratio > 80)
			return (w_ratio / 5 + 1);
		return (w_ratio);
	}
	else
	{
		if (h_ratio > 80)
			return (h_ratio / 5 + 1);
		return (h_ratio);
	}
}

void	initial_translate(t_fdf_data *fdf, t_camera *new)
{
	t_vector3	*mid;
	int			x;
	int			y;

	x = fdf->map_size[0] / 2;
	y = fdf->map_size[1] / 2;
	mid = get_camera_view(fdf, y, x);
	new->translate_x = WIN_WIDTH / 2 - mid->x;
	new->translate_y = WIN_HEIGHT / 2 - mid->y;
	free(mid);
}

void	new_camera(t_fdf_data *fdf)
{
	t_camera	*camera;

	camera = (t_camera *) ft_calloc(1, sizeof(t_camera));
	if (!camera)
		mlx_close(fdf, 2, "Error: Camera allocation failed");
	fdf->camera = camera;
	camera->rotation_x = 35;
	camera->rotation_z = 45;
	camera->scale = initial_scale(fdf);
	camera->translate_x = 0;
	camera->translate_y = 0;
	initial_translate(fdf, camera);
}
