/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:39:47 by jebouche          #+#    #+#             */
/*   Updated: 2023/01/30 16:31:06 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "ft_printf.h"

// t_vector3	*new_vector3(void)
// {
// 	t_vector3	*new;

// 	new = (t_vector3 *) ft_calloc(1, sizeof(t_vector3));
// 	new->x = 0;
// 	new->y = 0;
// 	new->z = 0;
// 	return (new);
// }
void	print_vector3(t_vector3 *vector, char *str)
{
	ft_printf("%s\n", str);
	ft_printf("Vector: %i, %i, %i\n", vector->x, vector->y, vector->z);
}

void	new_camera(t_fdf_data *fdf)
{
	t_camera	*camera;

	camera = (t_camera *) ft_calloc(1, sizeof(t_camera));
	if (!camera)
		mlx_close(fdf, 2, "Camera allocation failed");
	camera->rotation_x = 0;
	camera->rotation_z = 45;
	camera->scale = 50;
	camera->translate_x = 500;
	camera->translate_y = 500;
	fdf->camera = camera;
}

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
	
	// y x
	// x = cam_view->x * cos(rad_x) + cam_view->y * sin(rad_x) * sin(rad_z) + cam_view->z * sin(rad_x) * cos(rad_z);
	// y = cam_view->y * cos(rad_z) + cam_view->z * -sin(rad_z);
	// z = cam_view->x * -sin(rad_x) + cam_view->y * cos(rad_x) * sin(rad_z) + cam_view->z * cos(rad_x) * cos(rad_z);

	// // x z
	x = cam_view->x * cos(rad_z) + cam_view->y * -sin(rad_z);
	y = cam_view->x * cos(rad_x) * sin(rad_z) + cam_view->y * cos(rad_z) * cos(rad_x) + cam_view->z * -sin(rad_x);
	z = cam_view->x * sin(rad_x) * sin(rad_z) + cam_view->y * cos(rad_z) * sin(rad_x) + cam_view->z * cos(rad_x);
	
	cam_view->x = x;
	cam_view->y = y;
	cam_view->z = z;
}

t_vector3	*get_camera_view(t_fdf_data *fdf, int	i, int j)
{
	t_vector3	*cam_view;

	cam_view = (t_vector3 *) ft_calloc(1, sizeof(t_vector3));
	if (!cam_view)
		mlx_close(fdf, 1, "camera vector allocation failed");
	cam_view->x = j;
	cam_view->y = i;
	cam_view->z = fdf->map[i][j];
	
	// print_vector3(cam_view, "Before changed");//
	scale_vector(fdf->camera, cam_view);
	// print_vector3(cam_view, "After scale");//
	rotate_cam_vector(fdf->camera, cam_view);
	// print_vector3(cam_view, "After rotate");//
	translate_point(fdf->camera, cam_view);
	// print_vector3(cam_view, "After translate");//

	// ft_printf("\n");
	return (cam_view);
}
//begin camera intialize and transforms


// /*fills camera view with allocated vectors*/
// void	init_camera_view(t_fdf_data *fdf, int index)
// {
// 	int	l;

// 	l = 0;
// 	while (l < fdf->map_size[0])
// 	{
// 		fdf->camera->camera_view[index][l] = new_vector3();
// 		if (!fdf->camera->camera_view[index][l])
// 			mlx_close(fdf, 2, "Camera view vector allocation failed");
// 		l++;
// 	}
// }

// void	init_camera(t_fdf_data *fdf)
// {
// 	t_camera	*camera;
// 	int			i;

// 	i = 0;
// 	camera = (t_camera *) ft_calloc(1, sizeof(t_camera));
// 	if (!camera)
// 		mlx_close(fdf, 2, "Camera allocation failed");
// 	camera->camera_view = (t_vector3 ***) ft_calloc(fdf->map_size[1], sizeof(t_vector3 **));
// 	if (!camera->camera_view)
// 		mlx_close(fdf, 2, "Camera view allocation failed");
// 	fdf->camera = camera;
// 	while (i < fdf->map_size[1])
// 	{
// 		camera->camera_view[i] = (t_vector3 **) ft_calloc(fdf->map_size[1], sizeof(t_vector3 **));
// 		if (!camera->camera_view[i])
// 			mlx_close(fdf, 2, "Camera view row allocation failed");
// 		init_camera_view(fdf, i);
// 		i++;
// 	}
// 	ft_printf("Camera made!\n");
// }
// /*copies and converts the vectors from the map to the camera, does not rotate view*/
// void	fill_camera_from_map(t_fdf_data *fdf)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < fdf->map_size[1])
// 	{	
// 		j = 0;
// 		while(j < fdf->map_size[0])
// 		{
// 			fdf->camera->camera_view[i][j]->x = j;
// 			fdf->camera->camera_view[i][j]->y = i;
// 			fdf->camera->camera_view[i][j]->z = fdf->map[i][j];
// 			j++;
// 		}
// 		i++;
// 	}
// 	ft_printf("Camera filled!\n");
// }
// //how to handle rounding...?
// void	rotate_cam_vector(t_vector3 *vector, double rad_x, double rad_y)
// {
// 	double	x;
// 	double	y;
// 	double	z;
// 	// y x
// 	x = vector->x * cos(rad_x) + vector->y * sin(rad_x) * sin(rad_y) + vector->z * sin(rad_x) * cos(rad_y);
// 	y = vector->y * cos(rad_y) + vector->z * -sin(rad_y);
// 	z = vector->x * -sin(rad_x) + vector->y * cos(rad_x) * sin(rad_y) + vector->z * cos(rad_x) * cos(rad_y);

// 	// // x z
// 	// x = vector->x * cos(rad_y) + vector->y * -sin(rad_y);
// 	// y = vector->x * cos(rad_x) * sin(rad_y) + vector->y * cos(rad_y) * cos(rad_x) + vector->z * -sin(rad_x);
// 	// z = vector->x * sin(rad_x) * sin(rad_y) + vector->y * cos(rad_y) * sin(rad_x) + vector->z * cos(rad_x);

// 	vector->x = x;
// 	vector->y = y;
// 	vector->z = z;
// }
// /*will change the camera view based on the angles passed for rotation, may not need z rotation*/
// void	rotate_camera_view(t_fdf_data *fdf, int deg_x, int deg_y)
// {
// 	int	i;
// 	int	j;
// 	double	rad_x;
// 	double	rad_y;

// 	i = 0;
// 	rad_x = deg_x * (M_PI / 180);
// 	rad_y = deg_y * (M_PI / 180);
// 	while (i < fdf->map_size[1])
// 	{	
// 		j = 0;
// 		while(j < fdf->map_size[0])
// 		{
// 			rotate_cam_vector(fdf->camera->camera_view[i][j], rad_x, rad_y);
// 			j++;
// 		}
// 		i++;
// 	}
// 	ft_printf("Camera rotated!\n");
// }



// void	scale_camera(t_fdf_data *fdf, int scalar)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	//if scalar is 0 it wil zero out all of the vectors... have to generate from the map again..
// 	while (i < fdf->map_size[1])
// 	{	
// 		j = 0;
// 		while(j < fdf->map_size[0])
// 		{
// 			scale_vector(fdf->camera->camera_view[i][j], scalar);
// 			j++;
// 		}
// 		i++;
// 	}
// 	ft_printf("Camera scaled!\n");
// }

// void	print_camera_vectors(t_fdf_data *fdf)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	//if scalar is 0 it wil zero out all of the vectors... have to generate from the map again..
// 	while (i < fdf->map_size[1])
// 	{	
// 		j = 0;
// 		while(j < fdf->map_size[0])
// 		{
// 			ft_printf("Vector 3: %i, %i, %i \n", fdf->camera->camera_view[i][j]->x, fdf->camera->camera_view[i][j]->y, fdf->camera->camera_view[i][j]->z);
// 			j++;
// 		}
// 		i++;
// 	}
// 	ft_printf("Camera printed!\n");
// }

// void	camera_iter(t_vector3 ***cam_view, void (*f)())
// {

// }

//end camera intialize and transforms