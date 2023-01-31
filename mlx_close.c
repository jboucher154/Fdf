/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:47:29 by jebouche          #+#    #+#             */
/*   Updated: 2023/01/31 17:10:55 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

void	free_str_2darr(char **to_free)
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

int	mlx_close(t_fdf_data *fdf, int exit_code, char *exit_msg)
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
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx)
		free(fdf->mlx);
	if (fdf)
		free(fdf);
	if (exit_code)
		ft_putendl_fd(exit_msg, 2);
	exit(exit_code);
	return (0);
}
