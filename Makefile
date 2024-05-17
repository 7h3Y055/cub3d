NAME      = cub3d
SRCS      = 2d23d_helpers.c  ft_parse.c          ft_parse_utils_1.c  init.c        main.c     mlx.c      moves.c   raycasting.c  utils_1.c  utils_3.c 3d.c\
            ft_parse_utils_0.c  ft_parse_utils_2.c  init_param.c  minimap.c  moves_0.c  obunga.c  utils_0.c     utils_2.c
OBJS      = $(SRCS:.c=.o)
INC       = ./includes
LIBFT_DIR = ./lib/libft
LIBFT     = ./lib/libft/libft.a
GNL		  = lib/gnl/get_next_line.c lib/gnl/get_next_line_utils.c
CFLAGS    = #-Wall -Werror -Wextra #-g -fsanitize=address
MLX_FLAGS = -lXext -lX11 -lm
CC        = cc

# MAC_FLAGS = -L /Users/mezzine/.brew/lib/X11/locale/common
# MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

all:$(NAME)

$(NAME):$(GNL) $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(MLX_FLAGS) $(CFLAGS) $(LIBFT) $(GNL) -I$(INC) -o $(NAME) $(MAC_FLAGS)  libmlx_Linux.a

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

