/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:32:43 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/01 17:48:47 by jebouche         ###   ########.fr       */
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

t_fdf_data	*new_fdf(void)
{
	t_fdf_data	*new;

	new = (t_fdf_data *) malloc(sizeof(t_fdf_data));
	if (!new)
	{
		ft_putendl_fd("Fdf allocation failed", 2);
		exit(1);
	}
	new->camera = NULL;
	new->img1 = NULL;
	new->map = NULL;
	new->map_size[0] = 0;
	new->map_size[1] = 0;
	new->mlx = NULL;
	new->win = NULL;
	new->dirty = 0;
	return (new);
}

t_fdf_data	*create_fdf(char *fname)
{
	t_fdf_data	*new;

	new = new_fdf();
	new->mlx = mlx_init();
	if (!new->mlx)
		mlx_close(new, 2, "mlx allocation failed");
	// new->win = mlx_new_window(new->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	// if (!new->win)
	// 	mlx_close(new, 2, "window allocation failed");
	// get_new_image(new);
	// new->map = get_map(fname, new);
	// new_camera(new);
	fname = 0;
	return (new);
}
