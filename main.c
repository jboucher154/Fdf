/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:54:03 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/06 16:30:15 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	t_fdf_data	fdf;

	if (argc == 1)
		exit(1);
	create_fdf(&fdf, argv[1]);
	draw_camera_view(&fdf);
	mlx_put_image_to_window((&fdf)->mlx, (&fdf)->win, (&fdf)->img1->img, 0, 0);
	mlx_hook((&fdf)->win, 17, 0, &mlx_close, &fdf);
	mlx_hook((&fdf)->win, 2, 1L << 0, handle_press, &fdf);
	mlx_loop((&fdf)->mlx);
	return (0);
}
