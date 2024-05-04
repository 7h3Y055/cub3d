NAME      = cub3d
SRCS      = main.c ft_parse.c utils.c mlx.c moves.c raycasting.c
OBJS      = $(SRCS:.c=.o)
INC       = ./includes
LIBFT_DIR = ./lib/libft
LIBFT     = ./lib/libft/libft.a
GNL		  = lib/gnl/get_next_line.c lib/gnl/get_next_line_utils.c
CFLAGS    = #-g -fsanitize=address #-Wall -Werror -Wextra
# MLX_FLAGS = -lXext -lX11 -lm
CC        = cc

MAC_FLAGS = -lmlx -framework OpenGL -framework AppKit -lm
X11 = -I /Users/mezzine/homebrew/lib/X11/locale/common

all:$(NAME)

$(NAME):$(GNL) $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(MLX_FLAGS) $(CFLAGS) $(LIBFT) libmlx_Linux.a $(GNL) -I$(INC) -o $(NAME) $(MAC_FLAGS)

%.o:%.c
	$(CC) $(CFLAGS) $< -c -I$(INC) -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)
fclean:clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)
re:fclean all

bonus:


# // t_point	ray(t_ptr *ptr, double a)
# // {
# // 	t_point	nexty;
# // 	t_point	ay;

# // 	init_param_y(ptr, &nexty, &ay, a);
# // 	while (!exeed_map(ptr, nexty))
# // 	{
# // 		if (ptr->map2d[(long long)(nexty.y / SCALE)][(long long)(nexty.x / SCALE)] != '0')
# // 			break ;
# // 		nexty.x += ay.x;
# // 		nexty.y += ay.y;
# // 	}
# // 	return (nexty);
# // }