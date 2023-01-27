/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:35:44 by jebouche          #+#    #+#             */
/*   Updated: 2023/01/27 14:42:52 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

int	get_width(char **split_line)
{
	int	width;

	width = 0;
	if (split_line)
		while (split_line[width])
			width++;
	return (width);
}

int	*convert_to_ints(int width, char **split_line)
{
	int	*num_arr;
	int	i;

	i = 0;
	num_arr = (int *) ft_calloc(width, sizeof(int));
	if (!num_arr)
		return (NULL);
	while (split_line[i])
	{
		num_arr[i] = ft_atoi(split_line[i]);
		i++;
	}
	return (num_arr);
}

int	**map_from_file(ssize_t fd, t_fdf_data *fdf)
{
	int		**map;
	char	*line;
	char 	**split_line;
	int		size[2];
	
	map = (int **) ft_calloc(1000, sizeof(int *)); //how big to reserve... should it double at some point?
	size[0] = 0;
	size[1] = 0;
	line = get_next_line(fd);
	while (line)
	{
		split_line = ft_split(line, ' ');
		if (!split_line)
		{
			close(fd);
			mlx_close(fdf, 2, "Map split failed");
		}
		if (split_line && size[0] == 0)
			size[0] = get_width(split_line);
		map[size[1]] = convert_to_ints(size[0], split_line);
		if (!map[size[1]])
		{
			close(fd);
			mlx_close(fdf, 2, "Map row allocation failed");
		}
		free (line);
		line = get_next_line(fd);
		size[1]++;
	}
	free (line);
	fdf->map_size[0] = size[0];
	fdf->map_size[1] = size[1];
	return (map);
}

int	**get_map(char *fname, t_fdf_data *fdf) //could also put fdf here to add the map dimensions...and send for freeing in case of error
{
	ssize_t	fd;
	int		**map;//could be made a 2d array of t_map_data...

	fd = open(fname, O_RDONLY);
	if (fd < 0)
		mlx_close(fdf, 2, "No such file or directory");
	map = map_from_file(fd, fdf);
	close(fd); //check for close error
	if (!map)
		mlx_close(fdf, 2, "Map allocation failed");
	return (map);
}
