/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:47:29 by jebouche          #+#    #+#             */
/*   Updated: 2023/01/30 15:36:58 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

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

int	mlx_close(t_fdf_data *fdf, int exit_code, char *exit_msg) //add string and number to this for error message and exit code
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
	if (fdf->camera)
		free(fdf->camera);
	mlx_destroy_window(fdf->mlx, fdf->win);
	free(fdf->mlx);
	free(fdf);
	if (exit_code)
		ft_putendl_fd(exit_msg, 2);
	exit(exit_code);
	return (0);
}