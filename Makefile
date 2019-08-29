NAME = doom-nukem

CC = gcc
CCF = -fsanitize=address
FLAGS = -Wall -Wextra
LIBRARIES = -lft -L$(LIBFT_DIR) $(SDL_DIR)
INCLUDES = -I$(HEADERS_DIR) -I$(LIBFT_HEAD) $(SDL_PATH)

SDL_DIR = -L$(HOME)/.brew/Cellar/sdl2/2.0.9_1/lib -lSDL2			\
		-L$(HOME)/.brew/Cellar/sdl2_ttf/2.0.15/lib -lSDL2_ttf		\
		-L$(HOME)/.brew/Cellar/sdl2_image/2.0.5/lib -lSDL2_image
SDL_PATH = -I $(HOME)/.brew/Cellar/sdl2/2.0.9_1/include/SDL2		\
		-I $(HOME)/.brew/Cellar/sdl2_ttf/2.0.15/include/SDL2		\
		-I $(HOME)/.brew/Cellar/sdl2_image/2.0.1_2/include/SDL2		\

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./Libft/
LIBFT_HEAD = $(LIBFT_DIR)

HEADERS_LIST = doom-nukem.h
HEADERS_DIR = ./includes/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRC_LIST = main.c 		\
		event_func.c	\
		edit.c			\
		parse_tex.c 	\
		main_loop.c 	\
		init.c 			\
		yeet.c

SRC_DIR = ./srcs/
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

YELLOW = \033[033m
GREEN = \033[032m
BLUE = \033[36m
RED = \033[031m
PURPLE = \033[35m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@if !(brew ls --versions sdl2) > /dev/null; then\
		brew install sdl2;\
	fi
	@echo "$(YELLOW)Sources compilation $(RESET)[$(GREEN)OK$(RESET)]\n"
	@$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJ) -o $(NAME)
	@echo "[$(BLUE)$(NAME) Compiled$(RESET)]"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "\n$(BLUE)Obj directory...$(RESET)[$(GREEN)created$(RESET)]\n"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(YELLOW)$(notdir $(basename $@))...$(RESET)[$(GREEN)OK$(RESET)]"

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)

clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "\n$(RED)Obj directory...$(RESET)[$(PURPLE)deleted$(RESET)]\n"

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(RED)Libft...$(RESET)[$(PURPLE)deleted$(RESET)]\n"
	@rm -f $(NAME)
	@echo "$(RED)$(NAME)...$(RESET)[$(PURPLE)deleted$(RESET)]\n"

sani :  $(LIBFT) $(OBJ_DIR) $(OBJ)
	@echo "$(YELLOW)Sources compilation $(RESET)[$(GREEN)OK$(RESET)]\n"
	@$(CC) $(CCF) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJ) -o $(NAME)
	@echo "[$(BLUE)$(NAME) Compiled$(RESET)]"

re: fclean all

.PHONY: all clean fclean re sani