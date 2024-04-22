SRC =	ft_toupper.c	ft_substr.c		ft_tolower.c		\
		ft_atoi.c		ft_bzero.c		ft_calloc.c			\
		ft_isalnum.c	ft_isalpha.c	ft_isascii.c		\
		ft_isdigit.c	ft_isprint.c	ft_itoa.c			\
		ft_memchr.c		ft_memcmp.c		ft_memcpy.c			\
		ft_memmove.c	ft_memset.c		ft_putchar_fd.c		\
		ft_putendl_fd.c	ft_putnbr_fd.c	ft_putstr_fd.c		\
		ft_split.c		ft_strchr.c		ft_strdup.c			\
		ft_striteri.c	ft_strjoin.c	ft_strlcat.c		\
		ft_strlcpy.c	ft_strlen.c		ft_strmapi.c		\
		ft_strncmp.c	ft_strnstr.c	ft_strrchr.c		\
		ft_strtrim.c	ft_strcmp.c	ft_strndup.c	ft_strstr.c	\
		ft_isspace.c
CFLAGS = -Wall -Wextra -Werror -I../../includes
NAME = libft.a
OBJ = $(subst .c,.o,$(SRC))

all:$(NAME)
$(NAME):$(OBJ)
	ar -rcs $(NAME) $(OBJ)

$(OBJ_B):$(SRC_B)
	gcc -c $(SRC_B) $(CFLAGS)
	ar -rcs $(NAME)

clean:
	rm -f $(OBJ)
fclean:clean
	rm -f $(NAME)
re:fclean all
.PHONY: all clean fclean re
