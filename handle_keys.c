/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbabela <mbabela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:37 by aberdai           #+#    #+#             */
/*   Updated: 2022/03/25 11:23:04 by mbabela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move(t_data *data)
{
	double	d[2];
	double	mv_speed;

	d[X] = 0.0;
	d[Y] = 0.0;
	if (!(data->pressed_keys
			& (W_KEY_PRSD | A_KEY_PRSD | S_KEY_PRSD | D_KEY_PRSD)))
		return ;
	if (data->pressed_keys & (W_KEY_PRSD | S_KEY_PRSD))
	{
		mv_speed = MV_SPEED * ternary(data->pressed_keys & S_KEY_PRSD, -1, 1);
		d[X] += data->dir[X] * mv_speed;
		d[Y] += data->dir[Y] * mv_speed;
	}
	if (data->pressed_keys & (D_KEY_PRSD | A_KEY_PRSD))
	{
		mv_speed = MV_SPEED * ternary(data->pressed_keys & A_KEY_PRSD, -1, 1);
		d[X] += data->plane[X] * mv_speed;
		d[Y] += data->plane[Y] * mv_speed;
	}
	if (data->map[(int)(data->pos[X] + d[X])][(int)(data->pos[Y] + d[Y])] != 0)
		return ;
	data->pos[X] += d[X];
	data->pos[Y] += d[Y];
}

static void	rotate(t_data *data)
{
	double	rot_speed;
	double	dir_x;

	if (!(data->pressed_keys
			& (LEFT_KEY_PRSD | RIGHT_KEY_PRSD)))
		return ;
	rot_speed = ROT_SPEED;
	if (data->pressed_keys & RIGHT_KEY_PRSD)
		rot_speed = -ROT_SPEED;
	dir_x = data->dir[X];
	data->dir[X] = dir_x * cos(rot_speed) - data->dir[Y] * sin(rot_speed);
	data->dir[Y] = dir_x * sin(rot_speed) + data->dir[Y] * cos(rot_speed);
	dir_x = data->plane[X];
	data->plane[X] = dir_x * cos(rot_speed) - data->plane[Y] * sin(rot_speed);
	data->plane[Y] = dir_x * sin(rot_speed) + data->plane[Y] * cos(rot_speed);
}

int	key_pressed(int key, t_data *data)
{
	if (key == ESC_KEY)
		close_win(data);
	else if (key == A_KEY)
		data->pressed_keys |= A_KEY_PRSD;
	else if (key == W_KEY)
		data->pressed_keys |= W_KEY_PRSD;
	else if (key == S_KEY)
		data->pressed_keys |= S_KEY_PRSD;
	else if (key == D_KEY)
		data->pressed_keys |= D_KEY_PRSD;
	else if (key == LEFT_KEY)
		data->pressed_keys |= LEFT_KEY_PRSD;
	else if (key == RIGHT_KEY)
		data->pressed_keys |= RIGHT_KEY_PRSD;
	else
		return (0);
	move(data);
	rotate(data);
	raycast(data);
	return (0);
}

int	key_released(int key, t_data *data)
{
	if (key == ESC_KEY)
		close_win(data);
	else if (key == A_KEY)
		data->pressed_keys &= ~A_KEY_PRSD;
	else if (key == W_KEY)
		data->pressed_keys &= ~W_KEY_PRSD;
	else if (key == S_KEY)
		data->pressed_keys &= ~S_KEY_PRSD;
	else if (key == D_KEY)
		data->pressed_keys &= ~D_KEY_PRSD;
	else if (key == LEFT_KEY)
		data->pressed_keys &= ~LEFT_KEY_PRSD;
	else if (key == RIGHT_KEY)
		data->pressed_keys &= ~RIGHT_KEY_PRSD;
	else
		return (0);
	move(data);
	rotate(data);
	raycast(data);
	return (0);
}
