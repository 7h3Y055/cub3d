NAME      = cub3D
SRCS      = 2d23d_helpers.c  ft_parse.c          ft_parse_utils_1.c  init.c        main.c     mlx.c      moves.c   raycasting.c  utils_1.c  utils_3.c 3d.c\
            ft_parse_utils_0.c  ft_parse_utils_2.c  init_param.c  minimap.c  moves_0.c  obunga.c  utils_0.c     utils_2.c
OBJS      = $(SRCS:.c=.o)
INC       = ./includes
LIBFT_DIR = ./lib/libft
LIBFT     = ./lib/libft/libft.a
GNL		  = lib/gnl/get_next_line.c lib/gnl/get_next_line_utils.c
CFLAGS    = -Wall -Werror -Wextra
MLX_FLAGS = -lXext -lX11 -lm -lmlx 
CC        = cc

all:$(NAME)

$(NAME):$(GNL) $(LIBFT) $(OBJS)
	@echo "cub3d_bonus ..."
	@$(CC) $(OBJS) $(MLX_FLAGS) $(CFLAGS) $(LIBFT) $(GNL) -I$(INC) -o $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) $< -c -I$(INC) -o $@

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

clean:
	@echo "clean"
	@make -s clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)

fclean:clean
	@echo "fclean"
	@make -s fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re:fclean all

