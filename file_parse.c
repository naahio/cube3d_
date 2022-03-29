/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberdai <aberdai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:13 by aberdai           #+#    #+#             */
/*   Updated: 2022/03/02 00:21:16 by aberdai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	parse_line(t_data *data, int fd, char *line, int ret)
{
	char	*tmp;

	tmp = line;
	while (*tmp && *tmp <= ' ')
		tmp++;
	if (*tmp == 'N' && *(tmp + 1) == 'O' && *(tmp + 2) == ' ')
		read_texture(data, fd, tmp + 2, &data->texture[NO]);
	else if (*tmp == 'S' && *(tmp + 1) == 'O' && *(tmp + 2) == ' ')
		read_texture(data, fd, tmp + 2, &data->texture[SO]);
	else if (*tmp == 'E' && *(tmp + 1) == 'A' && *(tmp + 2) == ' ')
		read_texture(data, fd, tmp + 2, &data->texture[EA]);
	else if (*tmp == 'W' && *(tmp + 1) == 'E' && *(tmp + 2) == ' ')
		read_texture(data, fd, tmp + 2, &data->texture[WE]);
	else if (*tmp == 'F' && *(tmp + 1) == ' ')
		read_color(data, fd, tmp + 1, &data->floor_col);
	else if (*tmp == 'C' && *(tmp + 1) == ' ')
		read_color(data, fd, tmp + 1, &data->ceilling_col);
	else
		try_read_map(data, fd, line, ret);
}

void	parse_file(t_data *data, int fd)
{
	char	*line;
	int		ret;

	ret = get_next_line(fd, &line);
	while (ret >= 0)
	{
		parse_line(data, fd, line, ret);
		sf_free(line);
		if (ret == 0)
			break ;
		ret = get_next_line(fd, &line);
	}
	if (ret == -1)
		cln_exit_close_fd(data, fd, "Error\nget_next_line returned -1\n");
	close(fd);
}
