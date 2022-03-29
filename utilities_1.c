/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberdai <aberdai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:22:06 by aberdai           #+#    #+#             */
/*   Updated: 2022/03/02 00:22:08 by aberdai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_win(t_data *data)
{
	cln_exit(data, EXIT_SUCCESS);
	return (0);
}

void	cln_exit(t_data *data, int status)
{
	if (status != EXIT_SUCCESS)
		perror("cub3D");
	data_finalize(data);
	exit(status);
}

void	cln_exit_close_fd(t_data *data, int fd, const char *error_msg)
{
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	if (fd > 2)
		close(fd);
	data_finalize(data);
	exit(EXIT_FAILURE);
}

void	*sf_calloc(t_data *data, size_t size)
{
	void	*ptr;
	char	*str;
	size_t	i;

	ptr = malloc(size);
	if (!ptr)
		cln_exit(data, EXIT_FAILURE);
	str = (char *)ptr;
	i = 0;
	while (i < size)
		str[i++] = (char)0;
	return (ptr);
}

void	sf_free(void *ptr)
{
	if (ptr)
		free(ptr);
}
