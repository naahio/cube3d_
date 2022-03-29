/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberdai <aberdai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:43 by aberdai           #+#    #+#             */
/*   Updated: 2022/03/02 00:21:45 by aberdai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
	{
		write(2, "usage: cub3D <filename>.cub\n", 28);
		return (EXIT_FAILURE);
	}
	data = data_init(av[1]);
	raycast(data);
	mlx_hook(data->win_ptr, 17, 0, close_win, data);
	mlx_hook(data->win_ptr, 2, 0, key_pressed, data);
	mlx_hook(data->win_ptr, 3, 0, key_released, data);
	mlx_loop(data->mlx_ptr);
	data_finalize(data);
	return (0);
}
