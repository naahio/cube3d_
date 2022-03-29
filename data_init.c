/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberdai <aberdai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:04 by aberdai           #+#    #+#             */
/*   Updated: 2022/03/02 00:21:06 by aberdai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	data_init_values(t_data *data)
{
	data->ceilling_col = -1;
	data->floor_col = -1;
	data->pos[X] = -1;
	data->pos[Y] = -1;
	data->dir[X] = -1;
	data->dir[Y] = -1;
	data->plane[X] = -1;
	data->plane[Y] = -1;
	data->map_height = -1;
	data->map_width = -1;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(
			data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	data->img = (t_mlx_img *)sf_calloc(data, sizeof(t_mlx_img));
	data->img->ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data->img->data = mlx_get_data_addr(
			data->img->ptr, &data->img->bits_per_pixel,
			&data->img->size_line, &data->img->endian);
}

static void	data_init_camera(t_data *data, int x, int y, char dir)
{
	if (data->pos[X] >= 0 || data->pos[Y] >= 0)
		cln_exit_close_fd(data, -1, "Error\nSetting up camera twice\n");
	data->pos[X] = x;
	data->pos[Y] = y;
	if (dir == 'E' || dir == 'W')
	{
		data->dir[X] = 0;
		data->dir[Y] = (-(dir == 'W') || 1);
		data->plane[X] = 0.66 * (-(dir == 'W') || 1);
		data->plane[Y] = 0;
	}
	else if (dir == 'S' || dir == 'N')
	{
		data->dir[X] = (-(dir == 'S') || 1);
		data->dir[Y] = 0;
		data->plane[X] = 0;
		data->plane[Y] = -0.66 * (-(dir == 'S') || 1);
	}
}

static void	check_map_data(t_data *data)
{
	int	i;
	int	j;

	if (data->pos[X] < 0 || data->pos[Y] < 0)
		cln_exit_close_fd(data, -1, "Error\nNo camera is set\n");
	j = -1;
	while (++j < data->map_width)
		if (data->map[0][j] == 0 || data->map[data->map_height - 1][j] == 0)
			cln_exit_close_fd(data, -1, "Error\nInvalid map\n");
	i = -1;
	while (++i < data->map_height)
		if (data->map[i][0] == 0 || data->map[i][data->map_width - 1] == 0)
			cln_exit_close_fd(data, -1, "Error\nInvalid map\n");
}

static void	init_int_map(t_data *data)
{
	int	i;
	int	j;
	int	k;

	data->map_height = word_count(data->raw_map, '\n');
	data->map = (int **)sf_calloc(data, sizeof(int *) * data->map_height);
	data->map_width = max_word_len(data->raw_map, '\n');
	k = 0;
	i = -1;
	while (++i < data->map_height)
	{
		data->map[i] = (int *)sf_calloc(data, sizeof(int) * data->map_width);
		j = 0;
		while (data->raw_map[k] && data->raw_map[k] != '\n')
		{
			if (data->raw_map[k] == '0' || data->raw_map[k] == '1')
				data->map[i][j++] = data->raw_map[k++] - '0';
			else
				data_init_camera(data, i, j++, data->raw_map[k++]);
		}
		while (j < data->map_width)
			data->map[i][j++] = 1;
		k += (data->raw_map[k] == '\n');
	}
	check_map_data(data);
}

t_data	*data_init(const char *filename)
{
	t_data	*data;
	int		fd;

	fd = sf_open(NULL, filename, ".cub", O_RDONLY);
	data = (t_data *)sf_calloc(NULL, sizeof(t_data));
	data_init_values(data);
	parse_file(data, fd);
	init_int_map(data);
	return (data);
}
