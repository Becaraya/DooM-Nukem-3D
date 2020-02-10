NAME = doom_nukem

CC = gcc
CCF = -fsanitize=address
OPT_FLAGS = -flto -O3
BUG_FLAGS = -g
FLAGS =  -Wall -Wextra
LIBRARIES = -L$(LIBFT_DIR) -lft
INCLUDES = -I$(HEADERS_DIR) -I$(LIBFT_HEAD) -I$(SDL_DIR)/SDL2


PWD = $(shell pwd)
SDL_DIR = $(shell pwd)/frameworks
FRAMEWORKS = -F $(SDL_DIR) -framework SDL2 -framework SDL2_ttf -framework SDL2_image -framework SDL2_mixer -Wl,-rpath $(SDL_DIR)

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./Libft/
LIBFT_HEAD = $(LIBFT_DIR)

HEADERS_LIST = doom_nukem.h
HEADERS_DIR = ./includes/
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

#init_two.c 				
#		init_troy.c 			
SRC_LIST = arrow_edit.c		\
		add_edit.c			\
		angles.c			\
		bad_pig.c			\
		bmp_to_tex.c		\
		choose_tex.c		\
		column_hits.c		\
		column_linesaver.c	\
		column_utils.c		\
		column.c			\
		draw_edit_tools.c	\
		draw_tools.c		\
		edit_link_sectors.c	\
		edit_to_game.c		\
		edit.c				\
		event_func.c		\
		ft_dtoa_doom.c		\
		finish.c			\
		game_disp.c			\
		game.c				\
		dead.c				\
		get_map.c			\
		get_map_two.c		\
		hms_parser.c		\
		hms_parser_sec.c	\
		hms_parser_tex.c	\
		hms_parser_texgp.c	\
		hms_encoder.c		\
		hms_encoder_sec.c	\
		hms_encoder_tex.c	\
		hms_encoder_texgp.c	\
		ia.c				\
		init.c 				\
		init_two.c			\
		init_troy.c			\
		main_loop.c 		\
		main.c				\
		mob_disp.c			\
		mob_moov.c			\
		mouse_edit_stat.c	\
		mouse_edit.c		\
		mouse_event_funk.c	\
		pewpew.c			\
		pimp_cross.c		\
		player_moov.c		\
		refresh_text.c		\
		rectanle_menu.c		\
		refresh.c			\
		render_cast.c		\
		render_minimap.c	\
		render_test.c		\
		render_utils.c		\
		render.c			\
		sdl_tools.c			\
		sector.c			\
		spawn.c				\
		set_edit.c			\
		sport_physics.c		\
		texte.c				\
		tool_add_edit.c		\
		tool_arrow.c		\
		tool_text.c			\
		tools.c				\
		won.c				\
		yeet_text.c			\
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

fast: all
	./doom_nukem house.hms

clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "\n$(RED)Obj directory...$(RESET)[$(PURPLE)deleted$(RESET)]\n"

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(RED)Libft...$(RESET)[$(PURPLE)deleted$(RESET)]\n"
	@rm -f $(NAME)
	@echo "$(RED)$(NAME)...$(RESET)[$(PURPLE)deleted$(RESET)]\n"

sani:  $(LIBFT) $(OBJ_DIR) $(OBJ)
	@echo "$(YELLOW)Sources compilation $(RESET)[$(GREEN)OK$(RESET)]\n"
	@$(CC) $(CCF) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJ) -o $(NAME)
	@echo "[$(BLUE)$(NAME) Compiled$(RESET)]"

bug: $(LIBFT) $(OBJ_DIR) $(OBJ)
	@echo "$(YELLOW)Sources compilation $(RESET)[$(GREEN)OK$(RESET)]\n"
	@$(CC) $(FRAMEWORKS) $(FLAGS) $(OPT_FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJ) -o $(NAME)
	@echo "[$(BLUE)$(NAME) Compiled$(RESET)]"
	lldb ./doom-nukem house.hms

re: fclean all

.PHONY: all clean fclean re sani bug run
