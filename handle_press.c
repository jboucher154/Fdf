/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:16:44 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/01 14:48:30 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"

void	change_translate(int key_code, t_fdf_data *fdf)
{
	if (key_code == 126)
		fdf->camera->translate_y -= 10;
	if (key_code == 125)
		fdf->camera->translate_y += 10;
	if (key_code == 123)
		fdf->camera->translate_x -= 10;
	if (key_code == 124)
		fdf->camera->translate_x += 10;
	fdf->dirty = 1;
}

void	change_scale(int key_code, t_fdf_data *fdf)
{
	if (key_code == 69)
		fdf->camera->scale += 2;
	if (key_code == 78)
		fdf->camera->scale -= 2;
	if (fdf->camera->scale <= 0)
		fdf->camera->scale = 1;
	fdf->dirty = 1;
}

void	change_rotation(int key_code, t_fdf_data *fdf)
{
	if (key_code == 91)
		fdf->camera->rotation_x -= 5;
	if (key_code == 84)
		fdf->camera->rotation_x += 5;
	if (key_code == 86)
		fdf->camera->rotation_z -= 5;
	if (key_code == 88)
		fdf->camera->rotation_z += 5;
	fdf->dirty = 1;
}

int	handle_press(int key_code, t_fdf_data *fdf)
{
	ft_printf("key pressed: %i\n", key_code);
	if (key_code == 53)
		mlx_close(fdf, 0, "Normal exit");
	if (key_code <= 126 && key_code >= 123)
		change_translate(key_code, fdf);
	if (key_code == 69 || key_code == 78)
		change_scale(key_code, fdf);
	if (key_code == 91 || key_code == 84 || key_code == 86 || key_code == 88)
		change_rotation(key_code, fdf);
	if (fdf->dirty == 1)
		redraw(fdf);
	return (0);
}
