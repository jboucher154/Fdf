/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_camera_view.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:39:47 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/07 14:22:10 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	translate_point(t_camera *camera, t_vector3 *cam_view)
{
	cam_view->x += camera->translate_x;
	cam_view->y += camera->translate_y;
}

void	scale_vector(t_camera *camera, t_vector3 *cam_view)
{
	cam_view->x = cam_view->x * camera->scale;
	cam_view->y = cam_view->y * camera->scale;
	cam_view->z = cam_view->z * camera->scale;
}

void	rotate_cam_vector(t_camera *camera, t_vector3 *cam_view)
{
	double	x;
	double	y;
	double	z;
	double	rad_x;
	double	rad_z;

	rad_x = camera->rotation_x * (M_PI / 180);
	rad_z = camera->rotation_z * (M_PI / 180);
	x = cam_view->x * cos(rad_z) + cam_view->y * -sin(rad_z);
	y = cam_view->x * cos(rad_x) * sin(rad_z) + cam_view->y * cos(rad_z) * \
	cos(rad_x) + cam_view->z * -sin(rad_x);
	z = cam_view->x * sin(rad_x) * sin(rad_z) + cam_view->y * cos(rad_z) * \
	sin(rad_x) + cam_view->z * cos(rad_x);
	cam_view->x = x;
	cam_view->y = y;
	cam_view->z = z;
}

static int	set_color(int z)
{
	if (z >= 1)
		return (0xFFFFFF);
	else if (z < 0)
		return (0xC71585);
	else
		return (0xDA70D6);
}

t_vector3	*get_camera_view(t_fdf_data *fdf, int i, int j)
{
	t_vector3	*cam_view;

	cam_view = (t_vector3 *) ft_calloc(1, sizeof(t_vector3));
	if (!cam_view)
		mlx_close(fdf, 1, "Error: Camera vector allocation failed");
	cam_view->x = j;
	cam_view->y = i;
	cam_view->z = fdf->map[i][j];
	cam_view->color = set_color(cam_view->z);
	scale_vector(fdf->camera, cam_view);
	rotate_cam_vector(fdf->camera, cam_view);
	translate_point(fdf->camera, cam_view);
	return (cam_view);
}
