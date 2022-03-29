/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberdai <aberdai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:20:43 by aberdai           #+#    #+#             */
/*   Updated: 2022/03/02 00:20:45 by aberdai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <unistd.h>
# include "get_next_line.h"
# include "keys.h"

# define VALID_MAP_ALPHABET	"01NSEW"
# define MV_SPEED			0.5
# define ROT_SPEED			0.3

typedef enum e_resolution
{
	WIN_HEIGHT = 720,
	WIN_WIDTH = 1280
}	t_resolution;

typedef enum e_dimension
{
	X,
	Y
}	t_dimension;

typedef enum e_direction
{
	NO,
	SO,
	EA,
	WE,
	E_DIR_SIZE
}	t_direction;

typedef struct s_mlx_img
{
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	void	*ptr;
	char	*data;
}	t_mlx_img;

typedef struct s_data
{
	int			floor_col;
	int			ceilling_col;
	int			map_width;
	int			map_height;
	int			pressed_keys;
	double		pos[2];
	double		dir[2];
	double		plane[2];
	char		*raw_map;
	int			**map;
	t_mlx_img	*texture[E_DIR_SIZE];
	void		*mlx_ptr;
	void		*win_ptr;
	t_mlx_img	*img;
}	t_data;

typedef struct s_render
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		camera_x;
	double		perp_wall_dist;
	double		wall_x;
	double		tex_pos;
	double		tex_step;
	int			map[2];
	int			step[2];
	int			tex[2];
	double		ray_dir[2];
	double		side_dist[2];
	double		delta_dist[2];
	t_mlx_img	*texture;
}	t_render;

t_data	*data_init(const char *filename);
void	data_finalize(t_data *data);

void	clr_img(t_data *data);
void	draw_ver_line(t_render *render, t_data *data, int x);
void	raycast(t_data *data);

int		key_pressed(int key, t_data *data);
int		key_released(int key, t_data *data);

void	parse_file(t_data *data, int fd);
void	read_color(t_data *data, int fd, const char *rgb, int *color);
void	read_texture(t_data *data, int fd,
			const char *path, t_mlx_img **texture);
void	try_read_map(t_data *data, int fd, const char *line, int ret);

int		close_win(t_data *data);
void	cln_exit(t_data *data, int status);
void	cln_exit_close_fd(t_data *data, int fd, const char *error_msg);
void	*sf_calloc(t_data *data, size_t size);
void	sf_free(void *ptr);
int		sf_open(t_data *data,
			const char *filename, const char *extension, int mode);

int		atouint8(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strtrim(char const *s1, char const *set);
int		word_count(char const *str, char sep);
size_t	max_word_len(const char *str, char sep);
int		ternary(int condition, int true, int false);

#endif
