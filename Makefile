NAME=cub3D
CC=gcc
CFLAGS=-Wall -Werror -Wextra
INCLUDES=.
LDIR=-L /usr/local/lib/
LIBS=-lmlx -framework OpenGL -framework AppKit
SRCS = 					\
atouint8.c				\
data_finalize.c			\
data_init.c				\
file_parse.c			\
ft_strcmp.c				\
ft_strtrim.c			\
get_next_line.c			\
get_next_line_utils.c	\
handle_keys.c			\
main.c					\
mlx_draw.c				\
raycast.c				\
read_color.c			\
read_map.c				\
read_texture.c			\
utilities_1.c			\
utilities_2.c			\
utilities_3.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) cub3D.h get_next_line.h keys.h
	$(CC) -o $(NAME) -I$(INCLUDES) $(filter-out %.h, $^) $(CFLAGS) $(LDIR) $(LIBS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
