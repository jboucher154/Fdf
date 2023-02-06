/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:35:44 by jebouche          #+#    #+#             */
/*   Updated: 2023/02/06 17:21:59 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <fcntl.h>

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
	while (i < width)
	{
		num_arr[i] = ft_atoi(split_line[i]);
		i++;
	}
	return (num_arr);
}

void	transfer_to_map(t_fdf_data *fdf, int fd, char **split_line, int **map)
{
	if (!split_line)
	{
		close(fd);
		mlx_close(fdf, 2, "Map split failed");
	}
	if (split_line && fdf->map_size[0] == 0)
		fdf->map_size[0] = get_width(split_line);
	map[fdf->map_size[1]] = convert_to_ints(fdf->map_size[0], split_line);
	if (!map[fdf->map_size[1]])
	{
		close(fd);
		mlx_close(fdf, 2, "Map row allocation failed");
	}
}

int	**map_from_file(ssize_t fd, t_fdf_data *fdf)
{
	int		**map;
	char	*row;
	char	**split_line;

	map = (int **) ft_calloc(1000, sizeof(int *));
	row = get_next_line(fd);
	split_line = NULL;
	while (row)
	{
		split_line = ft_split(row, ' ');
		transfer_to_map(fdf, fd, split_line, map);
		free_str_2darr(split_line);
		free(row);
		row = NULL;
		row = get_next_line(fd);
		fdf->map_size[1] += 1;
	}
	return (map);
}

int	**get_map(char *fname, t_fdf_data *fdf)
{
	ssize_t	fd;
	size_t	r;
	int		**map;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
		mlx_close(fdf, 2, "No such file or directory");
	map = map_from_file(fd, fdf);
	r = close(fd);
	if (r < 0)
		mlx_close(fdf, 2, "Close failed");
	if (!map)
		mlx_close(fdf, 2, "Map allocation failed");
	return (map);
}
