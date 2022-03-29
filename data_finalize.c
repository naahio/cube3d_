/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_finalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberdai <aberdai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:20:51 by aberdai           #+#    #+#             */
/*   Updated: 2022/03/02 00:20:53 by aberdai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	data_finalize(t_data *data)
{
	int	i;

	if (data)
	{
		sf_free(data->raw_map);
		i = -1;
		while (++i < data->map_height)
			sf_free(data->map[i]);
		i = -1;
		while (++i < E_DIR_SIZE)
		{
			if (data->texture[i] && data->texture[i]->ptr)
				mlx_destroy_image(data->mlx_ptr, data->texture[i]->ptr);
			sf_free(data->texture[i]);
		}
		if (data->img && data->img->ptr)
			mlx_destroy_image(data->mlx_ptr, data->img->ptr);
		sf_free(data->img);
	}
}
