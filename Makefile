NAME      = cub3d
SRCS      = ft_parse.c  ft_parse_utils_0.c  ft_parse_utils_1.c  ft_parse_utils_2.c  main.c  minimap.c  mlx.c  moves.c moves_0.c  obunga.c  raycasting.c  tmp.c  utils_0.c  utils_1.c  utils_2.c
OBJS      = $(SRCS:.c=.o)
INC       = ./includes
LIBFT_DIR = ./lib/libft
LIBFT     = ./lib/libft/libft.a
GNL		  = lib/gnl/get_next_line.c lib/gnl/get_next_line_utils.c
CFLAGS    = -g3 #-fsanitize=address #-Wall  #-Werror -Wextra
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

bonus:

# save rays in array

# death sound https://www.youtube.com/watch?v=CNVbPpXCC1c&ab_channel=F4Playzz
# death sound https://www.youtube.com/watch?v=Vk4KK-gh0FM&ab_channel=NostalgiaChannel
# intro sounf https://youtu.be/fcwOIz2jwkM?si=2BIqd165a5VUwsDT
# https://www.youtube.com/watch?v=7qKlU2a9-Zg&ab_channel=MemeSoundEffects
# game sound https://youtu.be/0bQJRumF59E?si=DME0h9lW7baNN8rD
# game sound https://youtu.be/KU0AdJh_AIU?si=QacsW9dsqcNQsFtG
# game sound https://youtu.be/RVzRwWVl9FU?si=4PW6RRZczg27bJF6
# https://youtu.be/UG0HtBg7KAk?si=ziDZEisQDBMAVoMc
# https://www.youtube.com/watch?v=cQKq-ti1CSs&ab_channel=UpscaledHistory

# https://www.youtube.com/watch?v=O7JPP1SY1dE&ab_channel=zakariaTalk

# coach zouhir 
# https://www.youtube.com/watch?v=SNhCQdBIOds&ab_channel=Alaa-EddineGuimimi

# https://www.youtube.com/watch?v=q8KyFepTGEg&ab_channel=MiawX2








