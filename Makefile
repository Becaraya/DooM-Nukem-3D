NAME = doom-nukem

CC = gcc
CCF = -fsanitize=address
OPT_FLAGS = -flto -O3
FLAGS = -Wall -Wextra
LIBRARIES = -lft -L$(LIBFT_DIR)
INCLUDES = -I$(HEADERS_DIR) -I$(LIBFT_HEAD) $(SDL_HEAD)

SDL_DIR = ./SDL2.framework/lib
SDL_HEAD = -I ./frameworks/SDL2.framework/Versions/A/Headers \
		-I ./frameworks/SDL2_ttf.framework/Versions/A/Headers \
		-I ./frameworks/SDL2_image.framework/Versions/A/Headers \
		-I ./frameworks/SDL2_mixer.framework/Headers \
		-I ./frameworks/SDL2_net.framework/Headers \
		-F ./frameworks

FRAMEWORKS = -F ./frameworks \
		-rpath ./frameworks \
		-framework OpenGL -framework AppKit -framework OpenCl \
		-framework SDL2 -framework SDL2_ttf -framework SDL2_image \
		-framework SDL2_mixer -framework SDL2_net

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./Libft/
LIBFT_HEAD = $(LIBFT_DIR)

HEADERS_LIST = doom-nukem.h
HEADERS_DIR = ./includes/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

SRC_LIST = main.c		\
		edit.c			\
		event_func.c	\
		game.c			\
		render.c		\
		angles.c		\
		sport_physics.c	\
		hms_parser.c	\
		hms_parser_sec.c\
		hms_parser_tex.c\
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
	@echo "$(YELLOW)Sources compilation $(RESET)[$(GREEN)OK$(RESET)]\n"
	@$(CC) $(FLAGS) $(OPT_FLAGS) $(LIBRARIES) $(INCLUDES) $(FRAMEWORKS) $(OBJ) -o $(NAME)
	@echo "[$(BLUE)$(NAME) Compiled$(RESET)]"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "\n$(BLUE)Obj directory...$(RESET)[$(GREEN)created$(RESET)]\n"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(FLAGS) $(OPT_FLAGS) -c $(INCLUDES) $< -o $@
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