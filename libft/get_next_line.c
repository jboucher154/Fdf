/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebouche <jebouche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:56:57 by jebouche          #+#    #+#             */
/*   Updated: 2023/01/16 14:41:21 by jebouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	read_to_buffer(char	*buffer, int fd, size_t *buff_index);
static void	add_to_string(char **dst, char *to_cpy, size_t *index, size_t len);
static char	*eof_or_error(char *line, int ret);
static int	copy_len(char *buffer, size_t b_index);

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	static size_t	b_index = BUFFER_SIZE;
	char			*line;
	int				read_ret;

	read_ret = 1;
	line = (char *) malloc(sizeof(char) * 1);
	if (line)
	{
		line[0] = '\0';
		while (ft_strchr(line, '\n') == NULL && read_ret > 0)
		{
			if (b_index == BUFFER_SIZE)
			{
				read_ret = read_to_buffer(buffer, fd, &b_index);
				if (read_ret == -1 || (read_ret == 0 && ft_strlen(line) == 0))
					return (eof_or_error(line, read_ret));
			}
			if (copy_len(buffer, b_index) == 0)
				return (eof_or_error(line, read_ret));
			add_to_string(&line, buffer, &b_index, copy_len(buffer, b_index));
		}
	}
	return (line);
}

static char	*eof_or_error(char *line, int ret)
{
	if (ret == -1 || (ret == 0 && ft_strlen(line) == 0) || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	else
		return (line);
}

static int	read_to_buffer(char	*buffer, int fd, size_t *buff_index)
{
	ssize_t	returned;

	returned = read(fd, buffer, BUFFER_SIZE);
	if (returned > 0)
	{
		buffer[returned] = '\0';
		*buff_index = 0;
	}
	return (returned);
}

static void	add_to_string(char **dst, char *to_cpy, size_t *index, size_t len)
{
	int		dest_index;
	int		i;
	char	*temp;

	i = 0;
	dest_index = ft_strlen(*dst);
	temp = (char *) malloc(sizeof(char) * (dest_index + len + 1));
	if (temp && dst)
	{
		while (i < dest_index)
		{
			temp[i] = (*dst)[i];
			i++;
		}
		free(*dst);
		*dst = temp;
		while (len > 0 && to_cpy)
		{
			(*dst)[dest_index++] = to_cpy[(*index)++];
			len--;
		}
		(*dst)[dest_index] = '\0';
	}
}

static int	copy_len(char *buffer, size_t b_index)
{
	int	i;

	i = 0;
	while (buffer[b_index] != '\0')
	{
		if (buffer[b_index] == '\n')
			return (i + 1);
		b_index++;
		i++;
	}
	return (i);
}
