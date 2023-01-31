/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:16:44 by jebouche          #+#    #+#             */
/*   Updated: 2023/01/31 16:21:10 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"

int	handle_press(int key_code, t_fdf_data *fdf)
{
	ft_printf("key pressed: %i\n", key_code);
	if (key_code == 53)
	{
		mlx_close(fdf, 0, "Normal exit");
	}
	return (0);
}
