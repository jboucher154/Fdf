/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:54:03 by jebouche          #+#    #+#             */
/*   Updated: 2023/01/31 13:36:21 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "ft_printf.h"
//begin custom mlx functions
void	my_mlx_pixel_put(t_img_data *data, t_vector3 *start, int color)
{
	char	*dst;

	if (start->x > WIN_WIDTH -1 || start->x < 0 || start->y > WIN_HEIGHT -1 || start->y < 0)
		return ;
	dst = data->addr + (start->y * data->line_length + start->x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	// ft_printf("pixel printed: %i, %i\n", start->x, start->y);
}
//end custom mlx functions

//begin project map
/*need to know where to transfrom the 0,0 vector to on the image, begin without a translate or scaling*/


//end project map

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
	new_camera(fdf);
	draw_camera_view(fdf);

	// start_vector.x = 500; ///////
	// start_vector.y = 357;
	// end.x = 535;
	// end.y = 300;
	// // draw_line(&start_vector, &end, 0xFF00FF, fdf);
	// bresneham_neg_steep(&start_vector, &end, 0xFF00FF, fdf);
	// my_mlx_pixel_put(fdf->img1, &start_vector, 0xFF0000);
	// my_mlx_pixel_put(fdf->img1, &end, 0xFF0000);
	
	// start_vector.x = 465; ///////
	// start_vector.y = 328;
	// end.x = 500;
	// end.y = 300;
	// // draw_line(&start_vector, &end, 0xFF00FF, fdf);
	// bresneham_neg_grad(&start_vector, &end, 0xFF0000, fdf);
	// my_mlx_pixel_put(fdf->img1, &start_vector, 0xFFFF00);
	// my_mlx_pixel_put(fdf->img1, &end, 0xFFFF00);

	///
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


// first_point(fdf, &start_vector);
	// next_point_right(fdf, &start_vector, fdf->map[0][1]);
	// ft_printf("first x: %i\n", start_vector.x);
	// ft_printf("first y: %i\n", start_vector.y);
	// next_point_left(fdf, &start_vector, fdf->map[1][0]);
	// my_mlx_pixel_put(fdf->img1, &start_vector, 0xFF0000);



//begin grid printing
// void	draw_cam_view(t_fdf_data *fdf, t_camera *camera)
// {
// 	/*draw rows linking to point left and down
// 	last element in row only draws down
// 	final row only links left*/
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < fdf->map_size[1])
// 	{
// 		j = 0;
// 		while (j < fdf->map_size[0])
// 		{
// 			if (j + 1 < fdf->map_size[0])
// 			{
// 				/*draw to left*/
// 				draw_line(camera->camera_view[i][j], camera->camera_view[i][j + 1], 0xFF00FF, fdf);
// 			}
// 			if (i + 1 < fdf->map_size[1])
// 			{
// 				/*draw down*/
// 				draw_line(camera->camera_view[i][j], camera->camera_view[i + 1][j], 0xFF00FF, fdf);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	ft_printf("Camera view drawn!\n");
// }

//end grid printing