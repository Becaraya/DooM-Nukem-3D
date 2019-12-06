NAME = doom-nukem

CC = gcc
CCF = -fsanitize=address
OPT_FLAGS = -flto -O3
FLAGS = -Wall -Wextra
LIBRARIES = -L$(LIBFT_DIR) -lft
INCLUDES = -I$(HEADERS_DIR) -I$(LIBFT_HEAD) -I$(SDL_DIR)/SDL2


PWD = $(shell pwd)
SDL_DIR = $(shell pwd)/frameworks
FRAMEWORKS = -F $(SDL_DIR) -framework SDL2 -framework SDL2_ttf -framework SDL2_image -framework SDL2_mixer -Wl,-rpath $(SDL_DIR)

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./Libft/
LIBFT_HEAD = $(LIBFT_DIR)

HEADERS_LIST = doom-nukem.h
HEADERS_DIR = ./includes/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRC_LIST = main.c			\
		edit.c				\
		event_func.c		\
		game.c				\
		render.c			\
		column.c			\
		angles.c			\
		sport_physics.c		\
		hms_parser.c		\
		hms_parser_sec.c	\
		hms_parser_tex.c	\
		hms_encoder.c		\
		hms_encoder_sec.c	\
		hms_encoder_tex.c	\
		bmp_to_tex.c		\
		parse_tex.c 		\
		main_loop.c 		\
		init.c 				\
		mouse_edit.c		\
		sdl_tools.c			\
		pimp_cross.c		\
		refresh.c			\
		sprite.c			\
		get_map.c			\
		entity.c			\
		yeet.c				\
		sector.c			\
		ia.c

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
	@echo "$(YELLOW)Sources compilation $(RESET)[$(GREEN)OK$(RESET)]\n"
	@$(CC) $(FRAMEWORKS) $(FLAGS) $(OPT_FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJ) -o $(NAME)
	@echo "[$(BLUE)$(NAME) Compiled$(RESET)]"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "\n$(BLUE)Obj directory...$(RESET)[$(GREEN)created$(RESET)]\n"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(FLAGS) $(OPT_FLAGS) -F $(SDL_DIR) -c $(INCLUDES) $< -o $@
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
