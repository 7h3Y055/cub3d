NAME      = cub3d
SRCS      = main.c ft_parse.c utils.c
OBJS      = $(SRCS:.c=.o)
INC       = ./includes
LIBFT_DIR = ./lib/libft
LIBFT     = ./lib/libft/libft.a
GNL		  = lib/gnl/get_next_line.c lib/gnl/get_next_line_utils.c
CFLAGS    = #-Wall -Werror -Wextra
CC        = cc

all:$(NAME)

$(NAME):$(GNL) $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(GNL) -I$(INC) -o $(NAME)

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