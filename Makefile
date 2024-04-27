NAME      = cub3d
SRCS      = main.c ft_parse.c utils.c mlx.c moves.c
OBJS      = $(SRCS:.c=.o)
INC       = ./includes
LIBFT_DIR = ./lib/libft
LIBFT     = ./lib/libft/libft.a
GNL		  = lib/gnl/get_next_line.c lib/gnl/get_next_line_utils.c
CFLAGS    = -g #-fsanitize=address# -Wall -Werror -Wextra
MLX_FLAGS = -lXext -lX11 -lm
# MAC_FLAGS = -lmlx -framework OpenGL -framework AppKit -lm
CC        = cc

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