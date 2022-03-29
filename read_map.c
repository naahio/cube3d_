/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberdai <aberdai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:59 by aberdai           #+#    #+#             */
/*   Updated: 2022/03/02 00:22:00 by aberdai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*rm_spaces(const char *str)
{
	char	*no_spaces;
	int		spaces_count;
	int		i;

	spaces_count = 0;
	i = -1;
	while (str[++i])
		if (str[i] <= ' ')
			spaces_count++;
	no_spaces = (char *)malloc(
			sizeof(char) * (ft_strlen(str) - spaces_count + 1));
	if (!no_spaces)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (*str > ' ')
			no_spaces[i++] = *str;
		str++;
	}
	no_spaces[i] = '\0';
	return (no_spaces);
}

static int	only_contains(const char *str, const char *valid_alpha)
{
	size_t	i;
	size_t	j;
	int		valid;

	i = -1;
	while (++i < ft_strlen(str))
	{
		valid = 0;
		j = -1;
		while (++j < ft_strlen(valid_alpha))
			if (str[i] == valid_alpha[j])
				valid = 1;
		if (!valid)
			return (0);
	}
	return (1);
}

static int	everything_is_set_before(t_data *data)
{
	return (data->texture[NO] && data->texture[NO]->ptr
		&& data->texture[SO] && data->texture[SO]->ptr
		&& data->texture[EA] && data->texture[EA]->ptr
		&& data->texture[WE] && data->texture[WE]->ptr
		&& data->floor_col != -1 && data->ceilling_col != -1);
}

static void	read_map_line(t_data *data, int fd, const char *map_line)
{
	char	*tmp;

	if (!everything_is_set_before(data))
		cln_exit_close_fd(data, fd,
			"Error\nSomething is missing\n");
	if (!data->raw_map)
		data->raw_map = ft_strdup(map_line);
	else
	{
		tmp = data->raw_map;
		data->raw_map = ft_strjoin(data->raw_map, map_line);
		sf_free(tmp);
	}
	tmp = data->raw_map;
	data->raw_map = ft_strjoin(data->raw_map, "\n");
	sf_free(tmp);
}

void	try_read_map(t_data *data, int fd, const char *line, int ret)
{
	char	*no_spaces;

	no_spaces = rm_spaces(line);
	if (ft_strlen(no_spaces) > 0
		&& only_contains(no_spaces, VALID_MAP_ALPHABET))
		read_map_line(data, fd, no_spaces);
	else if (ft_strlen(no_spaces) > 0
		&& !only_contains(no_spaces, VALID_MAP_ALPHABET))
		cln_exit_close_fd(data, fd,
			"Error\nInvalid alphabet used in map definition\n");
	else if (data->raw_map && ret > 0)
		cln_exit_close_fd(data, fd,
			"Error\nEmpty line in middle of map definition\n");
	sf_free(no_spaces);
}
