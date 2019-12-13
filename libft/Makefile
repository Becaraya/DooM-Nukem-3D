NAME = libft.a

CC = gcc

FLAGS = -Wall -Werror -Wextra
CFLAGS = -c $(FLAGS)

OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

SRC = ft_memset.c \
	ft_bzero.c \
	ft_abs.c	\
	ft_memcpy.c \
	ft_memccpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strlen.c \
	ft_strdup.c \
	ft_strcpy.c \
	ft_strncpy.c \
	ft_strcat.c \
	ft_strncat.c \
	ft_strlcat.c \
	ft_strrchr.c \
	ft_strchr.c \
	ft_strstr.c \
	ft_strnstr.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_atoi.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_memalloc.c \
	ft_memdel.c \
	ft_strnew.c \
	ft_strdel.c \
	ft_strclr.c \
	ft_striter.c \
	ft_striteri.c \
	ft_strmap.c \
	ft_strmapi.c \
	ft_strequ.c \
	ft_strsub.c \
	ft_strjoin.c \
	ft_strjoin_free_f.c \
	ft_strnequ.c \
	ft_strsplit.c \
	ft_strtrim.c \
	ft_itoa.c \
	ft_putchar.c \
	ft_putstr.c \
	ft_putendl.c \
	ft_putnbr.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstnew.c \
	ft_lstdelone.c \
	ft_lstdel.c \
	ft_lstadd.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_is_prime.c \
	ft_sqrt.c \
	ft_swap.c \
	ft_power.c \
	ft_isblank.c \
	get_next_line.c

BLUE = \033[36m
RESET   = \033[0m
	
all : $(OBJ_DIR) $(NAME)
	@echo "\n$(BLUE)Libft Ready Sir !$(RESET)"

$(NAME): $(OBJ)
	@ar rc $@ $^
	@ranlib $@

$(addprefix $(OBJ_DIR), %.o) : %.c
	@$(CC) $(CFLAGS) -o $@ $<
	@echo -n '.'

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all, clean, fclean, re
