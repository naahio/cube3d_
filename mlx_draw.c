/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberdai <aberdai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:50 by aberdai           #+#    #+#             */
/*   Updated: 2022/03/02 00:21:52 by aberdai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_tex_coordinates(t_render *r, t_data *d)
{
	r->tex[X] = (int)(r->wall_x * r->texture->width);
	if ((r->texture == d->texture[NO]
			|| r->texture == d->texture[SO]) && r->ray_dir[X] > 0)
			r->tex[X] = r->texture->width - r->tex[X] - 1;
	if ((r->texture == d->texture[EA]
			|| r->texture == d->texture[WE]) && r->ray_dir[Y] > 0)
			r->tex[X] = r->texture->width - r->tex[X] - 1;
	r->tex_step = (double)r->texture->height / r->line_height;
	r->tex_pos = (r->draw_start - WIN_HEIGHT
			/ 2.0 + r->line_height / 2.0) * r->tex_step;
}

static int	get_color_from_texture(t_render *r)
{
	char	*ptr;
	int		pixel;

	pixel = r->tex[Y] * r->texture->size_line + r->tex[X] * 4;
	ptr = r->texture->data + pixel;
	if (r->texture->endian == 0)
		return ((((unsigned char)ptr[2]) << 16)
			+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
	return ((((unsigned char)ptr[0]) << 16)
		+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[2]));
}

static void	pixel_put(t_data *data, int x, int y, int color)
{
	int	pixel;

	if (data->img->bits_per_pixel != 32)
		color = mlx_get_color_value(data->mlx_ptr, color);
	pixel = (y * data->img->size_line) + (x * 4);
	if (data->img->endian == 1)
	{
		data->img->data[pixel + 0] = (color >> 24);
		data->img->data[pixel + 1] = (color >> 16) & 0xFF;
		data->img->data[pixel + 2] = (color >> 8) & 0xFF;
		data->img->data[pixel + 3] = (color) & 0xFF;
	}
	else if (data->img->endian == 0)
	{
		data->img->data[pixel + 0] = (color) & 0xFF;
		data->img->data[pixel + 1] = (color >> 8) & 0xFF;
		data->img->data[pixel + 2] = (color >> 16) & 0xFF;
		data->img->data[pixel + 3] = (color >> 24);
	}
}

void	draw_ver_line(t_render *render, t_data *data, int x)
{
	int	y;

	y = 0;
	while (y < render->draw_start)
		pixel_put(data, x, y++, data->ceilling_col);
	init_tex_coordinates(render, data);
	while (y < render->draw_end)
	{
		render->tex[Y] = (int)render->tex_pos & (render->texture->height - 1);
		render->tex_pos += render->tex_step;
		pixel_put(data, x, y++, get_color_from_texture(render));
	}
	while (y < WIN_HEIGHT)
		pixel_put(data, x, y++, data->floor_col);
}

void	clr_img(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			pixel_put(data, x, y, 0);
	}
}
