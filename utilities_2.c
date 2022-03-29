/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberdai <aberdai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:22:10 by aberdai           #+#    #+#             */
/*   Updated: 2022/03/02 00:22:11 by aberdai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	valid_extension(const char *filename, const char *extension)
{
	size_t	filename_len;
	size_t	extension_len;

	filename_len = ft_strlen(filename);
	extension_len = ft_strlen(extension);
	if (filename_len <= extension_len
		|| ft_strcmp(filename + filename_len - extension_len, extension) != 0)
		return (0);
	return (1);
}

int	sf_open(t_data *data, const char *filename, const char *extension, int mode)
{
	int	fd;

	if (extension && !valid_extension(filename, extension))
	{
		write(STDERR_FILENO, "cube3D: ", 8);
		write(STDERR_FILENO, filename, ft_strlen(filename));
		write(STDERR_FILENO, ": invalid extension\n", 20);
		data_finalize(data);
		exit(EXIT_FAILURE);
	}
	fd = open(filename, mode);
	if (fd < 0)
		cln_exit(data, EXIT_FAILURE);
	return (fd);
}
