/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberdai <aberdai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:53 by aberdai           #+#    #+#             */
/*   Updated: 2022/03/02 00:21:55 by aberdai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	render_init(t_render *r, t_data *d, int x)
{
	r->camera_x = 2.0 * x / WIN_WIDTH - 1.0;
	r->ray_dir[X] = d->dir[X] + d->plane[X] * r->camera_x;
	r->ray_dir[Y] = d->dir[Y] + d->plane[Y] * r->camera_x;
	r->map[X] = (int)d->pos[X];
	r->map[Y] = (int)d->pos[Y];
	r->side_dist[X] = 0.0;
	r->side_dist[Y] = 0.0;
	r->delta_dist[X] = fabs(1 / r->ray_dir[X]);
	if (r->ray_dir[X] == 0)
		r->delta_dist[X] = 1e30;
	r->delta_dist[Y] = fabs(1 / r->ray_dir[Y]);
	if (r->ray_dir[Y] == 0)
		r->delta_dist[Y] = 1e30;
	r->perp_wall_dist = 0.0;
	r->step[X] = 0.0;
	r->step[Y] = 0.0;
	r->texture = NULL;
}

static void	compute_side_dists(t_render *r, t_data *d)
{
	if (r->ray_dir[X] < 0)
	{
		r->step[X] = -1;
		r->side_dist[X] = (d->pos[X] - r->map[X]) * r->delta_dist[X];
	}
	else
	{
		r->step[X] = 1;
		r->side_dist[X] = (r->map[X] + 1.0 - d->pos[X]) * r->delta_dist[X];
	}
	if (r->ray_dir[Y] < 0)
	{
		r->step[Y] = -1;
		r->side_dist[Y] = (d->pos[Y] - r->map[Y]) * r->delta_dist[Y];
	}
	else
	{
		r->step[Y] = 1;
		r->side_dist[Y] = (r->map[Y] + 1.0 - d->pos[Y]) * r->delta_dist[Y];
	}
}

static void	dda(t_render *r, t_data *d)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (r->side_dist[X] < r->side_dist[Y])
		{
			r->side_dist[X] += r->delta_dist[X];
			r->map[X] += r->step[X];
			r->texture = d->texture[SO];
			if (r->ray_dir[X] > 0)
				r->texture = d->texture[NO];
		}
		else
		{
			r->side_dist[Y] += r->delta_dist[Y];
			r->map[Y] += r->step[Y];
			r->texture = d->texture[WE];
			if (r->ray_dir[Y] > 0)
				r->texture = d->texture[EA];
		}
		if (d->map[r->map[X]][r->map[Y]] > 0)
			hit = 1;
	}
}

static void	compute_line_height(t_render *r, t_data *d)
{
	if (r->texture == d->texture[NO] || r->texture == d->texture[SO])
		r->perp_wall_dist = r->side_dist[X] - r->delta_dist[X];
	else
		r->perp_wall_dist = r->side_dist[Y] - r->delta_dist[Y];
	r->line_height = (int)(WIN_HEIGHT / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2.0 + WIN_HEIGHT / 2.0;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2.0 + WIN_HEIGHT / 2.0;
	if (r->draw_end >= WIN_HEIGHT)
		r->draw_end = WIN_HEIGHT - 1;
	if (r->texture == d->texture[NO] || r->texture == d->texture[SO])
		r->wall_x = d->pos[Y] + r->perp_wall_dist * r->ray_dir[Y];
	else
		r->wall_x = d->pos[X] + r->perp_wall_dist * r->ray_dir[X];
	r->wall_x -= floor(r->wall_x);
}

void	raycast(t_data *data)
{
	t_render	render;
	int			x;

	clr_img(data);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		render_init(&render, data, x);
		compute_side_dists(&render, data);
		dda(&render, data);
		compute_line_height(&render, data);
		draw_ver_line(&render, data, x);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->ptr, 0, 0);
}
