/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:32:43 by jebouche          #+#    #+#             */
/*   Updated: 2023/01/31 16:43:55 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		fdf->img1->addr = mlx_get_data_addr(fdf->img1->img, \
		&fdf->img1->bits_per_pixel, &fdf->img1->line_length, \
		&fdf->img1->endian);
	fdf->img2 = my_new_image(fdf);
	if (fdf->img2)
		fdf->img2->addr = mlx_get_data_addr(fdf->img2->img, \
		&fdf->img2->bits_per_pixel, &fdf->img2->line_length, \
		&fdf->img2->endian);
	if (!fdf->img1 || !fdf->img2)
		mlx_close(fdf, 1, "Image allocation failed");
}

t_fdf_data	*new_fdf(void)
{
	t_fdf_data	*new;

	new = (t_fdf_data *) malloc(sizeof(t_fdf_data));
	if (!new)
		mlx_close(NULL, 2, "fdf allocation failed");
	new->camera = NULL;
	new->img1 = NULL;
	new->img2 = NULL;
	new->map = NULL;
	new->map_size[0] = 0;
	new->map_size[1] = 0;
	new->mlx = NULL;
	new->win = NULL;
	return (new);
}

t_fdf_data	*create_fdf(char *fname)
{
	t_fdf_data	*new;

	new = new_fdf();
	new->mlx = mlx_init();
	if (!new->mlx)
		mlx_close(new, 2, "mlx allocation failed");
	new->win = mlx_new_window(new->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!new->win)
		mlx_close(new, 2, "window allocation failed");
	set_images(new);
	new->map = get_map(fname, new);
	new_camera(new);
	return (new);
}
