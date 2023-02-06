/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:32:43 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/06 16:30:08 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	get_new_image(t_fdf_data *fdf)
{
	t_img_data	*img;

	img = (t_img_data *) malloc(sizeof(t_img_data));
	if (!img)
		mlx_close(fdf, 1, "Image allocation failed");
	img->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img->img)
		mlx_close(fdf, 1, "Image allocation failed");
	fdf->img1 = img;
	fdf->img1->addr = mlx_get_data_addr(fdf->img1->img, \
	&fdf->img1->bits_per_pixel, &fdf->img1->line_length, \
	&fdf->img1->endian);
}

void	new_fdf_setup(t_fdf_data *fdf)
{
	fdf->camera = NULL;
	fdf->img1 = NULL;
	fdf->map = NULL;
	fdf->map_size[0] = 0;
	fdf->map_size[1] = 0;
	fdf->mlx = NULL;
	fdf->win = NULL;
	fdf->dirty = 0;
}

void	create_fdf(t_fdf_data *fdf, char *fname)
{
	new_fdf_setup(fdf);
	fdf->map = get_map(fname, fdf);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		mlx_close(fdf, 2, "Mlx allocation failed");
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!fdf->win)
		mlx_close(fdf, 2, "Window allocation failed");
	get_new_image(fdf);
	new_camera(fdf);
}
