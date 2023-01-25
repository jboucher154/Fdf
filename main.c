/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:54:03 by jebouche          #+#    #+#             */
/*   Updated: 2023/01/25 17:52:02 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "ft_printf.h"
//begin custom mlx functions
void	my_mlx_pixel_put(t_img_data *data, t_vector3 *start, int color)
{
	char	*dst;

	// ft_printf("pixel put coords x: %i\n", start->x);
	// ft_printf("pixel put coords y: %i\n", start->y);
	dst = data->addr + (start->y * data->line_length + start->x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
//end custom mlx functions

//begin bresneham
/*need to add special cases for slopes > 1 and < -1 */
void	set_temps(t_vector3 *one, t_vector3 *two, t_vector3 *first, t_vector3 *second)
{
	// one = (t_vector3 *) ft_calloc(1, sizeof(t_vector3));
	// two = (t_vector3 *) ft_calloc(1, sizeof(t_vector3));
	// if (one && two)
	// {
		one->x = first->x;
		one->y = first->y;
		two->x = second->x;
		two->y = second->y;
	// }
}
void	bresneham_pos_grad(t_vector3 *first, t_vector3 *second, int color, t_fdf_data *fdf)
{
	t_vector3	deltas;
	t_vector3	one;
	t_vector3	two;
	int			decision;

	set_temps(&one, &two, first, second);
	// if (!one || !two)
	// 	mlx_close(fdf);
	deltas.x = two.x - one.x;
	deltas.y = two.y - one.y;
	decision = 2 * deltas.y - deltas.x;
	// ft_printf("bresneham one temp coords xy: %i , %i\n", one.x, one.y);
	// ft_printf("bresneham two temp coords xy: %i , %i\n", two.x, two.y);
	// ft_printf("non temp coords first x, y: %i, %i\n", first->x, first->y);
	// ft_printf("non temp coords second x, y: %i, %i\n", second->x, second->y);
	while (one.x < two.x)
	{
		my_mlx_pixel_put(fdf->img1, &one, color);
		// ft_printf("bresneham pixel printed\n");
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
	decision = 2 * deltas.x - deltas.y;
	while (one.y < two.y)
	{
		my_mlx_pixel_put(fdf->img1, &one, color);
		// ft_printf("bresneham pixel printed\n");
		if (decision >= 0)
		{
			one.x += 1;
			decision = decision + 2 * deltas.x - 2 * deltas.y;
		}
		else
		{
			decision = decision + 2 * deltas.y;
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
	while (one.x < two.x)
	{
		my_mlx_pixel_put(fdf->img1, &one, color);
		if (decision >= 0)
		{
			one.y -= 1;
			decision = decision - 2 * deltas.y + 2 * deltas.x;
		}
		else
		{
			decision = decision - 2 * deltas.y;
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
	while (one.y < two.y)
	{
		my_mlx_pixel_put(fdf->img1, &one, color);
		if (decision >= 0)
		{
			one.x -= 1;
			decision = decision - 2 * deltas.x + 2 * deltas.y;
		}
		else
		{
			decision = decision - 2 * deltas.x;
		}
		one.y += 1;
	}
}
//end bresneham

//hook handling and exiting
void	free_int_2darr(int **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

int	mlx_close(t_fdf_data *fdf) //add string and number to this for error message and exit code
{
	if (fdf->img1)
	{
		mlx_destroy_image(fdf->mlx, fdf->img1->img);
		free(fdf->img1);
	}
	if (fdf->img2)
	{
		mlx_destroy_image(fdf->mlx, fdf->img2->img);
		free (fdf->img2);
	}
	if (fdf->map)
		free_int_2darr(fdf->map);
	//free camera and contents
	mlx_destroy_window(fdf->mlx, fdf->win);
	free(fdf->mlx);
	free(fdf);
	exit(0);
	return (0);
}

int	handle_press(int key_code, t_fdf_data *fdf)
{
	ft_printf("key pressed: %i\n", key_code);
	if (key_code == 53)
	{
		mlx_close(fdf);
	}
	return (0);
}
//end hook handling

//begin grid printing --->may not need any of this section anymore...
void	first_point(t_fdf_data *fdf, t_vector3 *first) //t_fdf_data *fdf, include as param for more complex deterination of first point llocation
{
	double	tri_height;
	double	hypo;

	hypo = sqrt((fdf->map_size[0] * fdf->map_size[0]) + (fdf->map_size[1] * fdf->map_size[1]));
	tri_height = (fdf->map_size[0] * fdf->map_size[1]) / hypo;
	first->x = WIN_WIDTH / 2 - tri_height + 10; // will have to make this better for large maps or rectangular maps...
	first->y = hypo + 10; //make this relate to height of map, size of squares, then half the remaining space
	// ft_printf("first x: %i\n", first->x);
	// ft_printf("first y: %i\n", first->y);
}

void	next_point_right(t_fdf_data *fdf, t_vector3 *first, int map_value)
{
	t_vector3	next;

	next.x = first->x + fdf->grid_height / 2;
	if (map_value == 0)
		next.y = first->y + fdf->grid_width / 2;
	else
		next.y = (first->y + fdf->grid_width / 2) - fdf->grid_height / map_value;
	// ft_printf("next right x: %i\n", next.x);
	// ft_printf("next right y: %i\n", next.y);
	bresneham_pos_grad(first, &next, 0x00FFFF, fdf);
}

void	next_point_left(t_fdf_data *fdf, t_vector3 *first, int map_value)
{
	t_vector3	next;

	next.x = first->x - fdf->grid_height / 2;
	if (map_value == 0)
		next.y = first->y + fdf->grid_width / 2;
	else
		next.y = (first->y + fdf->grid_width / 2) - fdf->grid_height / map_value;
	// ft_printf("next left x: %i\n", next.x);
	// ft_printf("next left y: %i\n", next.y);
	bresneham_neg_grad(&next, first, 0xFF0000, fdf);
}

// void	draw_next_lines(t_fdf_data *fdf, t_vector3 *start, t_vector3 *index)
// {
// 	if (index->x == fdf->map_size[0] && index->y == fdf->map_size[1])
// 		return ;//trigger the drawing of the lines...
// 	else if (index->x == fdf->map_size[0])
// 		//keep finding the points for all of the y..
// 	else if (index->y == fdf->map_size[0])
// 		//keep finding the points for x...
// 	else 
// 		//find the next point...right and left
// }

// void 	draw_wireframe(t_fdf_data *fdf, t_vector3 *start)
// {
// 	t_vector3	index;

// 	index.x = 0;
// 	index.y = 0;
// 	draw_next_lines(fdf, start, &index);

// }
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
			mlx_close(fdf);
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
		mlx_close(fdf);
	camera->camera_view = (t_vector3 ***) ft_calloc(fdf->map_size[1], sizeof(t_vector3 **));
	if (!camera->camera_view)
		mlx_close(fdf);
	fdf->camera = camera;
	while (i < fdf->map_size[1])
	{
		camera->camera_view[i] = (t_vector3 **) ft_calloc(fdf->map_size[1], sizeof(t_vector3 **));
		if (!camera->camera_view[i])
			mlx_close(fdf);
		init_camera_view(fdf, i);
		i++;
	}
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
}
//how to handle rounding...?
void	transform_cam_vector(t_vector3 *vector, double rad_x, double rad_y)
{
	double	x;
	double	y;
	double	z;

	x = vector->x * cos(rad_x) + vector->y * sin(rad_x) * sin(rad_y) + vector->z * sin(rad_x) * cos(rad_y);
	y = vector->y * cos(rad_y) + vector->z * -sin(rad_y);
	z = vector->x * -sin(rad_x) + vector->y * cos(rad_x) * sin(rad_y) + vector->z * cos(rad_x) * cos(rad_y);
	vector->x = x;
	vector->y = y;
	vector->z = z;
}
/*will change the camera view based on the angles passed for rotation, may not need z rotation*/
void	transform_camera_view(t_fdf_data *fdf, int deg_x, int deg_y)
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
			transform_cam_vector(fdf->camera->camera_view[i][j], rad_x, rad_y);
			j++;
		}
		i++;
	}
}

//end camera intialize and transforms

//begin project map
/*need to know where to transfrom the 0,0 vector to on the image, begin without a translate or scaling*/


//end project map

//begin map input handling
int	get_width(char **split_line)
{
	int	width;

	width = 0;
	if (split_line)
		while (split_line[width])
			width++;
	return (width);
}

int	*convert_to_ints(int width, char **split_line)
{
	int	*num_arr;
	int	i;

	i = 0;
	num_arr = (int *) ft_calloc(width, sizeof(int));
	if (!num_arr)
		return (NULL);
	while (split_line[i])
	{
		num_arr[i] = ft_atoi(split_line[i]);
		i++;
	}
	return (num_arr);
}

int	**map_from_file(ssize_t fd, t_fdf_data *fdf)
{
	int		**map;
	char	*line;
	char 	**split_line;
	int		size[2];
	
	map = (int **) ft_calloc(1000, sizeof(int *)); //how big to reserve... should it double at some point?
	size[0] = 0;
	size[1] = 0;
	line = get_next_line(fd);
	while (line)
	{
		split_line = ft_split(line, ' ');
		if (size[0] == 0)
			size[0] = get_width(split_line);
		map[size[1]] = convert_to_ints(size[0], split_line);
		if (!map[size[1]])
		{
			free_int_2darr(map);
			return (NULL);
		}
		free (line);
		line = get_next_line(fd);
		size[1]++;
	}
	free (line);
	fdf->map_size[0] = size[0];
	fdf->map_size[1] = size[1];
	return (map);
}

int	**get_map(char *fname, t_fdf_data *fdf) //could also put fdf here to add the map dimensions...and send for freeing in case of error
{
	ssize_t	fd;
	int		**map;//could be made a 2d array of t_map_data...

	fd = open(fname, O_RDONLY);
	if (fd < 0)
		mlx_close(fdf); //is this the right return? or should prog exit???
	map = map_from_file(fd, fdf);
	close(fd); //check for close error
	if (!map)
		mlx_close(fdf);
	return (map);
}
//end map input handling

//begin initialize the fdf struct
t_img_data	*my_new_image(t_fdf_data *fdf)
{
	t_img_data	*img;

	img = (t_img_data *) malloc(sizeof(t_img_data));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	return (img);
}

void	set_images(t_fdf_data *fdf)
{
	fdf->img1 = my_new_image(fdf);
	if (fdf->img1)
		fdf->img1->addr = mlx_get_data_addr(fdf->img1->img, &fdf->img1->bits_per_pixel, &fdf->img1->line_length, &fdf->img1->endian);
	fdf->img2 = my_new_image(fdf);
	if (fdf->img2)
		fdf->img2->addr = mlx_get_data_addr(fdf->img2->img, &fdf->img2->bits_per_pixel, &fdf->img2->line_length, &fdf->img2->endian);
	if (!fdf->img1 || !fdf->img2)
		mlx_close(fdf);
}

t_fdf_data	*new_fdf(void)
{
	 t_fdf_data *new;

	 new  = (t_fdf_data *) malloc(sizeof(t_fdf_data));
	 if (!new)
		return (NULL);
	new->mlx = mlx_init();
	if (!new->mlx)
	{
		free(new);
		return (NULL);
	}
	new->win = mlx_new_window(new->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!new->win)
	{
		free(new->mlx);
		free(new);
		return (NULL);
	}
	set_images(new);
	return (new);
}
//end initialize fdf struct

//begin setup for map based variables
void	set_grid_size(t_fdf_data **fdf)
{
	double	hypo;
	double	grids_per_window;
	int		grid_size;

	hypo = sqrt(((*fdf)->map_size[0] * ((*fdf)->map_size[0])) + ((*fdf)->map_size[1] * ((*fdf)->map_size[1])));
	grids_per_window = (WIN_WIDTH - 20) / hypo;
	grid_size = round(grids_per_window);
	if (grid_size % 2 != 0)
		grid_size--;
	(*fdf)->grid_height = grid_size;
	(*fdf)->grid_width = grid_size;
	ft_printf("grid size: %i\n", grid_size);
}
//end setup for map based variables

int	main(int argc, char **argv)
{
	t_vector3	start_vector;
	t_vector3	end;
	t_fdf_data	*fdf;

	if (argc == 1)
		exit(1);
	fdf = new_fdf();
	if (!fdf)
		exit(1);
	fdf->map = get_map(argv[1], fdf); // already exited if error
	set_grid_size(&fdf);
	ft_printf("I got the map!\n");
	// first_point(fdf, &start_vector);
	// next_point_right(fdf, &start_vector, fdf->map[0][1]);
	// ft_printf("first x: %i\n", start_vector.x);
	// ft_printf("first y: %i\n", start_vector.y);
	// next_point_left(fdf, &start_vector, fdf->map[1][0]);
	// my_mlx_pixel_put(fdf->img1, &start_vector, 0xFF0000);
	start_vector.x = 200;
	start_vector.y = 200;
	end.x = 250;
	end.y = 500;
	bresneham_pos_steep(&start_vector, &end, 0xFF00FF, fdf);
	// start_vector.x = 400;
	// start_vector.y = 200;
	// end.x = 425;
	// end.y = 50;
	// bresneham_neg_steep(&end, &start_vector, 0x00FFFF, fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img1->img, 0, 0);
	mlx_hook(fdf->win, 17, 0, &mlx_close, fdf);
	mlx_hook(fdf->win, 2, 1L<<0, handle_press, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}

//what is the offset?
//int offset = (y * line_length + x * (bits_per_pixel /8));
// int	main(void)
// {
// 	// t_img_data	img;
// 	t_vector	start_vector;
// 	t_mlx_data	mlx_data;

// 	start_vector.x = 5;
// 	start_vector.y = 5;
// 	mlx_data.mlx = mlx_init();
// 	mlx_data.mlx_win = mlx_new_window(mlx_data.mlx, 1920, 1080, "My first window!");
// 	mlx_data.img->img = mlx_new_image(mlx_data.mlx, 1920, 1080);
// 	mlx_data.img->addr = mlx_get_data_addr(mlx_data.img->img, &(mlx_data.img->bits_per_pixel), &(mlx_data.img->line_length), &(mlx_data.img->endian));
// 	// my_mlx_pixel_put(&img, &start_vector, 0x00FF0000);
// 	// my_put_line_h(&img, &start_vector, 20);
// 	// my_put_line_v(&img, &start_vector, 20);
// 	// my_put_square(&img, &start_vector, 80);
// 	// my_put_circle(&img, 5, 5, 40);
	
// 	my_put_grid(mlx_data.img, &start_vector, 100, 10);
// 	// mlx_put_image_to_window(mlx_data.mlx, mlx_data.mlx_win, mlx_data.img->img, 0, 0);
// 	// mlx_hook(mlx_data.mlx_win, 17, 0L, &close, &mlx_data);
// 	mlx_loop(mlx_data.mlx);
// 	// mlx_destroy_window(mlx_ptr, mlx_win);
// 	// mlx_destroy_display(mlx_ptr);
// 	// free(mlx_data.mlx);
// 	return (0);
// }


// write to one image and prints two lines, pos and neg slope
// int	main(void)
// {
// 	// t_img_data	img;
// 	t_vector	start_vector;
// 	t_vector	end_vector;
// 	t_fdf_data	*fdf;
// 	// t_img_data	*img_one;

// 	start_vector.x = 5;
// 	start_vector.y = 5;
// 	end_vector.x = 500;
// 	end_vector.y = 400;
// 	fdf = (t_fdf_data *) malloc(sizeof(t_fdf_data));
// 	fdf->img1 = (t_img_data *) malloc(sizeof(t_img_data));
// 	fdf->mlx = mlx_init();
// 	fdf->win = mlx_new_window(fdf->mlx, 1920, 1080, "My first window!");
// 	fdf->img1->img = mlx_new_image(fdf->mlx, 1920, 1080);
// 	fdf->img1->addr = mlx_get_data_addr(fdf->img1->img, &fdf->img1->bits_per_pixel, &fdf->img1->line_length, &fdf->img1->endian);
// 	// fdf->img1 = img_one;
// 	// my_mlx_pixel_put(fdf->img1, &start_vector, 0x00ffff);
// 	bresneham_line_pos(&start_vector, &end_vector, 0x00FFFF, fdf);
// 	start_vector.x = 100;
// 	start_vector.y = 600;
// 	end_vector.x = 500;
// 	end_vector.y = 100;
// 	bresneham_line_neg(&start_vector, &end_vector, 0xFF0000, fdf);
// 	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img1->img, 0, 0);
// 	mlx_hook(fdf->win, 17, 0, &mlx_close, fdf);
// 	mlx_hook(fdf->win, 2, 1L<<0, handle_press, fdf);
// 	// mlx_key_hook(fdf->win, handle_press, fdf);
// 	mlx_loop(fdf->mlx);
// 	return (0);
// }