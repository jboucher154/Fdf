/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:48:33 by jebouche          #+#    #+#             */
/*   Updated: 2023/01/31 16:44:07 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "ft_printf.h"

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
		if (w_ratio > 30)
			return (w_ratio / 10 + 1);
		return (w_ratio);
	}
	else
	{
		if (h_ratio > 30)
			return (h_ratio / 10 + 1);
		return (h_ratio);
	}
}

void	new_camera(t_fdf_data *fdf)
{
	t_camera	*camera;

	camera = (t_camera *) ft_calloc(1, sizeof(t_camera));
	if (!camera)
		mlx_close(fdf, 2, "Camera allocation failed");
	camera->rotation_x = 35;
	camera->rotation_z = 45;
	camera->scale = initial_scale(fdf);
	camera->translate_x = (WIN_WIDTH - fdf->map_size[0] * camera->scale) / 2;
	camera->translate_y = (WIN_HEIGHT - fdf->map_size[1] * camera->scale) / 2;
	fdf->camera = camera;
}
