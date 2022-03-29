/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberdai <aberdai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:56 by aberdai           #+#    #+#             */
/*   Updated: 2022/03/02 00:21:57 by aberdai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	read_color(t_data *data, int fd, const char *rgb, int *color)
{
	int	tmp;
	int	i;

	if (*color != -1)
		cln_exit_close_fd(data, fd, "Error\nSetting same color twice\n");
	*color = 0;
	i = -1;
	while (++i < 3)
	{
		while (*rgb == ' ')
			rgb++;
		if (*rgb < '0' || *rgb > '9')
			cln_exit_close_fd(data, fd, "Error\nInvalid color\n");
		tmp = atouint8(rgb);
		if (tmp == -1)
			cln_exit_close_fd(data, fd, "Error\nInvalid color\n");
		*color = (*color << 8) + tmp;
		while (*rgb >= '0' && *rgb <= '9')
			rgb++;
		if (*rgb == ',' || i == 2)
			rgb++;
		else
			cln_exit_close_fd(data, fd, "Error\nInvalid color\n");
	}
}
