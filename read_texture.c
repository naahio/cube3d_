/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberdai <aberdai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:22:02 by aberdai           #+#    #+#             */
/*   Updated: 2022/03/02 00:22:04 by aberdai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	read_texture(t_data *data, int fd,
			const char *path, t_mlx_img **texture)
{
	char	*trimmed;

	if (*texture)
		cln_exit_close_fd(data, fd, "Error\nSetting same texture twice\n");
	trimmed = ft_strtrim(path, " ");
	*texture = (t_mlx_img *)sf_calloc(data, sizeof(t_mlx_img));
	(*texture)->ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			trimmed, &(*texture)->width, &(*texture)->height);
	if (!(*texture)->ptr)
		cln_exit_close_fd(data, fd, "Error\nCould not read texture file\n");
	(*texture)->data = mlx_get_data_addr(
			(*texture)->ptr, &(*texture)->bits_per_pixel,
			&(*texture)->size_line, &(*texture)->endian);
}
