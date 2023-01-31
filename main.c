/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:54:03 by jebouche          #+#    #+#             */
/*   Updated: 2023/01/31 16:44:46 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "ft_printf.h"

void	my_mlx_pixel_put(t_img_data *data, t_vector3 *pt, int color)
{
	char	*dst;

	if (pt->x >= WIN_WIDTH || pt->x < 0 || pt->y >= WIN_HEIGHT || pt->y < 0)
		return ;
	dst = data->addr + (pt->y * data->line_length + pt->x * \
	(data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(int argc, char **argv)
{
	t_fdf_data	*fdf;

	if (argc == 1)
		exit(1);
	fdf = create_fdf(argv[1]);
	if (!fdf)
		exit(1);
	draw_camera_view(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img1->img, 0, 0);
	mlx_hook(fdf->win, 17, 0, &mlx_close, fdf);
	mlx_hook(fdf->win, 2, 1L << 0, handle_press, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
