#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 1080
# endif
# ifndef WIN_WIDTH 
#  define WIN_WIDTH 1920
# endif

typedef struct	s_img_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img_data;

typedef struct				s_fdf_data
{
	void					*mlx;
	void					*win;
	struct s_img_data		*img1;
	struct s_img_data		*img2;
	int						**map;
	int						map_size[2];
	int						grid_height;
	int						grid_width;
}							t_fdf_data;
//add starting coord to the struct?

typedef struct	s_coords
{
	int	x;
	int	y;
}				t_coords;
//not sure if I need this....
// typedef struct	s_map_data
// {
// 	int			z_value;
// 	int			color;
// }				t_map_data;

#endif
