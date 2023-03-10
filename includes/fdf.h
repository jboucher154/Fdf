/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:39:49 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/07 14:22:37 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 1080
# endif
# ifndef WIN_WIDTH
#  define WIN_WIDTH 1920
# endif

typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img_data;

typedef struct s_fdf_data
{
	void					*mlx;
	void					*win;
	struct s_img_data		*img1;
	struct s_camera			*camera;
	int						**map;
	int						map_size[2];
	int						dirty;
}							t_fdf_data;

typedef struct s_vector3
{
	int	x;
	int	y;
	int	z;
	int	color;
}				t_vector3;

typedef struct s_camera
{
	int					rotation_x;
	int					rotation_z;
	int					scale;
	int					translate_x;
	int					translate_y;
}						t_camera;

void		draw_line(t_vector3 *f, t_vector3 *s, t_fdf_data *fdf);
void		my_mlx_pixel_put(t_img_data *data, t_vector3 *start, int color);
int			mlx_close(t_fdf_data *fdf, int exit_code, char *exit_msg);
int			handle_press(int key_code, t_fdf_data *fdf);
void		create_fdf(t_fdf_data *fdf, char *fname);
int			**get_map(char *fname, t_fdf_data *fdf);
t_vector3	*get_camera_view(t_fdf_data *fdf, int i, int j);
void		new_camera(t_fdf_data *fdf);
void		draw_camera_view(t_fdf_data *fdf);
void		free_str_2darr(char **to_free);
void		set_temps(t_vector3 *one, t_vector3 *two, t_vector3 *first, \
			t_vector3 *second);
void		redraw(t_fdf_data *fdf);
void		get_new_image(t_fdf_data *fdf);
int			set_line_color(t_vector3 *first, t_vector3 *second);
void		draw_vertical(t_vector3 *first, t_vector3 *second, int color, \
			t_fdf_data *fdf);

#endif
