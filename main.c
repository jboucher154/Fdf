/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:54:03 by jebouche          #+#    #+#             */
/*   Updated: 2023/01/27 15:07:43 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "ft_printf.h"
//begin custom mlx functions
void	my_mlx_pixel_put(t_img_data *data, t_vector3 *start, int color)
{
	char	*dst;

	dst = data->addr + (start->y * data->line_length + start->x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
//end custom mlx functions

//begin grid printing
void	draw_cam_view(t_fdf_data *fdf, t_camera *camera)
{
	/*draw rows linking to point left and down
	last element in row only draws down
	final row only links left*/
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map_size[1])
	{
		j = 0;
		while (j < fdf->map_size[0])
		{
			if (j + 1 < fdf->map_size[0])
			{
				/*draw to left*/
				draw_line(camera->camera_view[i][j], camera->camera_view[i][j + 1], 0xFF00FF, fdf);
			}
			if (i + 1 < fdf->map_size[1])
			{
				/*draw down*/
				draw_line(camera->camera_view[i][j], camera->camera_view[i + 1][j], 0xFF00FF, fdf);
			}
			j++;
		}
		i++;
	}
	ft_printf("Camera view drawn!\n");
}

//end grid printing

//begin camera intialize and transforms

t_vector3	*new_vector3(void)
{
	t_vector3	*new;

	new = (t_vector3 *) ft_calloc(1, sizeof(t_vector3));
	return (new);
}
/*fills camera view with allocated vectors*/
void	init_camera_view(t_fdf_data *fdf, int index)
{
	int	l;

	l = 0;
	while (l < fdf->map_size[0])
	{
		fdf->camera->camera_view[index][l] = new_vector3();
		if (!fdf->camera->camera_view[index][l])
			mlx_close(fdf, 2, "Camera view vector allocation failed");
		l++;
	}
}

void	init_camera(t_fdf_data *fdf)
{
	t_camera	*camera;
	int			i;

	i = 0;
	camera = (t_camera *) ft_calloc(1, sizeof(t_camera));
	if (!camera)
		mlx_close(fdf, 2, "Camera allocation failed");
	camera->camera_view = (t_vector3 ***) ft_calloc(fdf->map_size[1], sizeof(t_vector3 **));
	if (!camera->camera_view)
		mlx_close(fdf, 2, "Camera view allocation failed");
	fdf->camera = camera;
	while (i < fdf->map_size[1])
	{
		camera->camera_view[i] = (t_vector3 **) ft_calloc(fdf->map_size[1], sizeof(t_vector3 **));
		if (!camera->camera_view[i])
			mlx_close(fdf, 2, "Camera view row allocation failed");
		init_camera_view(fdf, i);
		i++;
	}
	ft_printf("Camera made!\n");
}
/*copies and converts the vectors from the map to the camera, does not rotate view*/
void	fill_camera_from_map(t_fdf_data *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map_size[1])
	{	
		j = 0;
		while(j < fdf->map_size[0])
		{
			fdf->camera->camera_view[i][j]->x = j;
			fdf->camera->camera_view[i][j]->y = i;
			fdf->camera->camera_view[i][j]->z = fdf->map[i][j];
			j++;
		}
		i++;
	}
	ft_printf("Camera filled!\n");
}
//how to handle rounding...?
void	rotate_cam_vector(t_vector3 *vector, double rad_x, double rad_y)
{
	double	x;
	double	y;
	double	z;
	// y x
	x = vector->x * cos(rad_x) + vector->y * sin(rad_x) * sin(rad_y) + vector->z * sin(rad_x) * cos(rad_y);
	y = vector->y * cos(rad_y) + vector->z * -sin(rad_y);
	z = vector->x * -sin(rad_x) + vector->y * cos(rad_x) * sin(rad_y) + vector->z * cos(rad_x) * cos(rad_y);

	// // x z
	// x = vector->x * cos(rad_y) + vector->y * -sin(rad_y);
	// y = vector->x * cos(rad_x) * sin(rad_y) + vector->y * cos(rad_y) * cos(rad_x) + vector->z * -sin(rad_x);
	// z = vector->x * sin(rad_x) * sin(rad_y) + vector->y * cos(rad_y) * sin(rad_x) + vector->z * cos(rad_x);

	vector->x = x;
	vector->y = y;
	vector->z = z;
}
/*will change the camera view based on the angles passed for rotation, may not need z rotation*/
void	rotate_camera_view(t_fdf_data *fdf, int deg_x, int deg_y)
{
	int	i;
	int	j;
	double	rad_x;
	double	rad_y;

	i = 0;
	rad_x = deg_x * (M_PI / 180);
	rad_y = deg_y * (M_PI / 180);
	while (i < fdf->map_size[1])
	{	
		j = 0;
		while(j < fdf->map_size[0])
		{
			rotate_cam_vector(fdf->camera->camera_view[i][j], rad_x, rad_y);
			j++;
		}
		i++;
	}
	ft_printf("Camera rotated!\n");
}

void	scale_vector(t_vector3 *vector, int scalar)
{
	vector->x = vector->x * scalar;
	vector->y = vector->y * scalar;
	vector->z = vector->z * scalar;
}

void	scale_camera(t_fdf_data *fdf, int scalar)
{
	int	i;
	int	j;

	i = 0;
	//if scalar is 0 it wil zero out all of the vectors... have to generate from the map again..
	while (i < fdf->map_size[1])
	{	
		j = 0;
		while(j < fdf->map_size[0])
		{
			scale_vector(fdf->camera->camera_view[i][j], scalar);
			j++;
		}
		i++;
	}
	ft_printf("Camera scaled!\n");
}

void	print_camera_vectors(t_fdf_data *fdf)
{
	int	i;
	int	j;

	i = 0;
	//if scalar is 0 it wil zero out all of the vectors... have to generate from the map again..
	while (i < fdf->map_size[1])
	{	
		j = 0;
		while(j < fdf->map_size[0])
		{
			ft_printf("Vector 3: %i, %i, %i \n", fdf->camera->camera_view[i][j]->x, fdf->camera->camera_view[i][j]->y, fdf->camera->camera_view[i][j]->z);
			j++;
		}
		i++;
	}
	ft_printf("Camera printed!\n");
}

// void	camera_iter(t_vector3 ***cam_view, void (*f)())
// {

// }

//end camera intialize and transforms

//begin project map
/*need to know where to transfrom the 0,0 vector to on the image, begin without a translate or scaling*/


//end project map


void	set_inital_scale(t_fdf_data *fdf)
{
	scale_camera(fdf, 50);
	/*determine initial scaling for map
	based on size of screen and size of map or of the coordinates of rotated ...
	maybe start with generic scaling of 50*/
	// ft_printf("Camera scaled!\n");
}
//end setup for map based variables

int	main(int argc, char **argv)
{
	// t_vector3	start_vector;
	// t_vector3	end;
	t_fdf_data	*fdf;

	if (argc == 1)
		exit(1);
	fdf = new_fdf();
	if (!fdf)
		exit(1);
	fdf->map = get_map(argv[1], fdf); // already exited if error
	// set_grid_size(&fdf);
	ft_printf("I got the map!\n");
	init_camera(fdf);
	fill_camera_from_map(fdf);
	print_camera_vectors(fdf);
	set_inital_scale(fdf);
	print_camera_vectors(fdf);
	rotate_camera_view(fdf, 45, 45);
	print_camera_vectors(fdf);
	draw_cam_view(fdf, fdf->camera);
	// first_point(fdf, &start_vector);
	// next_point_right(fdf, &start_vector, fdf->map[0][1]);
	// ft_printf("first x: %i\n", start_vector.x);
	// ft_printf("first y: %i\n", start_vector.y);
	// next_point_left(fdf, &start_vector, fdf->map[1][0]);
	// my_mlx_pixel_put(fdf->img1, &start_vector, 0xFF0000);
	// start_vector.x = 200;
	// start_vector.y = 200;
	// end.x = 250;
	// end.y = 600;
	// draw_line(&start_vector, &end, 0xFF00FF, fdf);
	// // bresneham_pos_steep(&start_vector, &end, 0xFF00FF, fdf);
	// // start_vector.x = 200;
	// // start_vector.y = 300;
	// // end.x = 150;
	// // end.y = 50;
	// start_vector.x = 200;
	// start_vector.y = 300;
	// end.x = 150;
	// end.y = 50;
	// draw_line(&start_vector, &end, 0x00FFFF, fdf);
	// // bresneham_neg_steep(&start_vector, &end, 0x00FFFF, fdf);
	// start_vector.x = 200;
	// start_vector.y = 300;
	// end.x = 200;
	// end.y = 50;
	// bresneham_neg_steep(&start_vector, &end, 0xFFFFFF, fdf);
	// start_vector.x = 300;
	// start_vector.y = 300;
	// end.x = 200;
	// end.y = 300;
	// // bresneham_neg_grad(&start_vector, &end, 0xFF0000, fdf);
	// draw_line(&start_vector, &end, 0xFF0000, fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img1->img, 0, 0);
	mlx_hook(fdf->win, 17, 0, &mlx_close, fdf);
	mlx_hook(fdf->win, 2, 1L<<0, handle_press, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}

//begin setup for map based variables
//not needed anymore...
// void	set_grid_size(t_fdf_data **fdf)
// {
// 	double	hypo;
// 	double	grids_per_window;
// 	int		grid_size;

// 	hypo = sqrt(((*fdf)->map_size[0] * ((*fdf)->map_size[0])) + ((*fdf)->map_size[1] * ((*fdf)->map_size[1])));
// 	grids_per_window = (WIN_WIDTH - 20) / hypo;
// 	grid_size = round(grids_per_window);
// 	if (grid_size % 2 != 0)
// 		grid_size--;
// 	(*fdf)->grid_height = grid_size;
// 	(*fdf)->grid_width = grid_size;
// 	ft_printf("grid size: %i\n", grid_size);
// }

//--->may not need any of this section anymore...
// void	first_point(t_fdf_data *fdf, t_vector3 *first) //t_fdf_data *fdf, include as param for more complex deterination of first point llocation
// {
// 	double	tri_height;
// 	double	hypo;

// 	hypo = sqrt((fdf->map_size[0] * fdf->map_size[0]) + (fdf->map_size[1] * fdf->map_size[1]));
// 	tri_height = (fdf->map_size[0] * fdf->map_size[1]) / hypo;
// 	first->x = WIN_WIDTH / 2 - tri_height + 10; // will have to make this better for large maps or rectangular maps...
// 	first->y = hypo + 10; //make this relate to height of map, size of squares, then half the remaining space
// 	// ft_printf("first x: %i\n", first->x);
// 	// ft_printf("first y: %i\n", first->y);
// }

// void	next_point_right(t_fdf_data *fdf, t_vector3 *first, int map_value)
// {
// 	t_vector3	next;

// 	next.x = first->x + fdf->grid_height / 2;
// 	if (map_value == 0)
// 		next.y = first->y + fdf->grid_width / 2;
// 	else
// 		next.y = (first->y + fdf->grid_width / 2) - fdf->grid_height / map_value;
// 	// ft_printf("next right x: %i\n", next.x);
// 	// ft_printf("next right y: %i\n", next.y);
// 	bresneham_pos_grad(first, &next, 0x00FFFF, fdf);
// }

// void	next_point_left(t_fdf_data *fdf, t_vector3 *first, int map_value)
// {
// 	t_vector3	next;

// 	next.x = first->x - fdf->grid_height / 2;
// 	if (map_value == 0)
// 		next.y = first->y + fdf->grid_width / 2;
// 	else
// 		next.y = (first->y + fdf->grid_width / 2) - fdf->grid_height / map_value;
// 	// ft_printf("next left x: %i\n", next.x);
// 	// ft_printf("next left y: %i\n", next.y);
// 	bresneham_neg_grad(&next, first, 0xFF0000, fdf);
// }
