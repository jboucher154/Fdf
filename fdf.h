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
	struct s_camera			*camera;
	int						**map;
	int						map_size[2];
	//add translate vector for 'placing' the map in the image,
	// check if it is  ' out of bounds and scale it to fit based on that instad of height and width
	int						grid_height;
	int						grid_width;
}							t_fdf_data;
//add starting coord to the struct?

typedef struct	s_vector3
{
	int	x;
	int	y;
	int z;
}				t_vector3;

typedef struct			s_camera
{
	struct s_vector3	***camera_view; //malloc for 2d array of vectors, does it need to be array? maybe...
	/* may need following data 
	rotation x
	rotation y
	origional points
	transformed points for projection
	*/
}						t_camera;

//not sure if I need this....
// typedef struct	s_map_data
// {
// 	int			z_value;
// 	int			color;
// }				t_map_data;

#endif
