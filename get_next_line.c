/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberdai <aberdai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:29 by aberdai           #+#    #+#             */
/*   Updated: 2022/03/02 00:21:30 by aberdai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_line(int fd, char **str)
{
	int		ret;
	char	*buf;
	char	*tmp;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (-1);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (*str)
		{
			tmp = *str;
			*str = ft_strjoin(*str, buf);
			free(tmp);
		}
		else
			*str = ft_strdup(buf);
		if (ft_indexof(*str, '\n') > 0)
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	static char		*str;
	int				i;
	char			*tmp;

	if (fd < 0 || !line || read(fd, str, 0) < 0)
		return (-1);
	if (!(ft_indexof(str, '\n') > 0))
		read_line(fd, &str);
	if (!str)
	{
		*line = ft_strdup("");
		return (0);
	}
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	*line = ft_substr(str, 0, i);
	tmp = NULL;
	if (str[i] == '\n')
		tmp = ft_strdup(str + i + 1);
	free(str);
	str = tmp;
	if (!str)
		return (0);
	return (1);
}
