SRCS = ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_memchr.c \
		ft_memset.c \
		ft_memcpy.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_strjoin.c \
		ft_strnstr.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_memmove.c \
		ft_atoi.c \
		ft_substr.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_putchar_fd.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_printf.c \
		check_flag.c \
		print_char.c \
		print_int.c \
		print_string.c \
		print_hex.c \
		print_pointer.c \


OBJ = ${SRCS:.c=.o}
NAME = libft.a
CFLAGS += -Wall -Werror -Wextra -I./include


${NAME} : ${OBJ} libft.h
	ar -crs libft.a ${OBJ}

all:	${NAME}

${OBJ} : libft.h


clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re:	fclean all

.PHONY : clean fclean re
