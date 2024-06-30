# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 18:35:04 by flfische          #+#    #+#              #
#    Updated: 2024/06/30 12:08:47 by flfische         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
MAKEFLAGS += --no-print-directory
NAME := miniRT
# DIRECTORIES
SRC_DIRS := src \
			src/mlx \
			src/errors \
			src/maths \
			src/objects \
			src/raytracer \
			src/colors \
			src/parsing \
			src/light \
			src/textures \

OBJ_DIR := obj
INC_DIR := includes
TMP_DIR := tmp

# FILES
vpath %.c $(SRC_DIRS)
vpath %.h $(INC_DIR)

CFILES := miniRT.c \
			init_rt.c \
			join_threads.c \
			mlx_init.c \
			mlx_hooks.c \
			print_error.c \

CFILES += 	parsing.c \
			parsing_handlers.c \
			parsing_utils.c \
			parsing_utils2.c \
			parsing_utils3.c \
			parse_camera.c \
			parse_material.c \
			parse_triangle.c \
			parse_cone.c \
			parse_cylinder.c \
			custom_split.c \

# OBJECTS
CFILES += get_first_obj.c \
			obj_func_getters.c \
			hit.c \
			camera.c \
			sphere.c \
			plane.c \
			cylinder.c \
			cylinder_utils.c \
			obj_utils.c \
			cone.c \
			triangle.c \

# RT
CFILES += send_rays.c \
			loop_pixels.c \

# COLORS
CFILES += avg_color.c \
			color_conversions.c \
			color_add.c \
			color_mult.c \

# LIGHT
CFILES += compute_ambient.c \
			compute_phong.c \
			compute_diffuse.c \
			compute_specular.c \

# MATHS
CFILES += random.c \
			v3_add.c \
			v3_copy.c \
			v3_crossprod.c \
			v3_div.c \
			v3_dotprod.c \
			v3_init.c \
			v3_len.c \
			v3_new.c \
			v3_normalize.c \
			v3_random.c \
			v3_scalar.c \
			v3_sub.c \


# MATERIALS
CFILES += check_materials.c \
			assign_mat_tex.c \

# TEXTURES

CFILES += checkerboard.c \
			parse_texture.c \
			file_textures.c \
			parse_bump.c \

OFILES := $(addprefix $(OBJ_DIR)/, $(CFILES:.c=.o))

HEADER_FILES := miniRT.h \
				config.h \
				objects.h \

INCLUDES := -I$(INC_DIR)

# LIBFT
LIBFT_DIR := libs/libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_FLAGS := -L$(LIBFT_DIR) -lft
INCLUDES += -I$(LIBFT_DIR)

# MLX42
MLX42_DIR := libs/MLX42
MLX42 =	$(MLX42_DIR)/build/libmlx42.a
MLX42_FLAGS =
ifeq ($(shell uname),Darwin)
	MLX42_FLAGS = -L$(MLX42_DIR)/build -lmlx42 -framework Cocoa -framework OpenGL -framework IOKit -lglfw
else ifeq ($(shell uname),Linux)
	MLX42_FLAGS = -L$(MLX42_DIR)/build -lmlx42 -Iinclude -ldl -lglfw -pthread -lm
endif
INCLUDES += -I$(MLX42_DIR)/include/MLX42

# RULES
all: ascii $(NAME)

$(NAME): $(LIBFT) $(MLX42) $(OFILES)
	@printf "\n$(YELLOW)Compiling $(NAME)...$(NC)\n"
	@$(CC) $(CFLAGS) -o $@ $(OFILES) $(LIBFT_FLAGS) $(MLX42_FLAGS)
	@if [ -f $(NAME) ]; then \
		echo "$(GREEN)$(NAME) compiled successfully!$(NC)"; \
		echo "$(CYAN)Run with ./$(NAME)$(NC)"; \
		echo "------------------------------------------------"; \
	else \
		echo "$(RED)$(NAME) failed to compile$(NC)"; \
	fi

$(OBJ_DIR)/%.o: %.c $(HEADER_FILES) | $(OBJ_DIR)
	@$(eval CURRENT := $(shell echo $$(($(CURRENT) + 1))))
	@$(eval PERCENT := $(shell echo $$(($(CURRENT) * 100 / $(TOTAL_SRCS)))))
	@printf "$(CLEAR_LINE)$(YELLOW)Compiling $(PERCENT)%% [$(CURRENT)/$(TOTAL_SRCS)] $(ITALIC_LIGHT_YELLOW)$<$(NC) "
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@echo "$(YELLOW)Creating obj directory...$(NC)"
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(NC)"
	@if [ ! -d $(LIBFT_DIR) ]; then mkdir -p $(LIBFT_DIR); fi
	@git submodule update --remote --init -q
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX42):
	@echo "$(YELLOW)Compiling mlx42...$(NC)"
	@if [ ! -d $(MLX42_DIR)/build ]; then mkdir -p $(MLX42_DIR)/build; fi
	@git submodule update --remote --init -q
	@cd $(MLX42_DIR)/build && cmake .. && make -j4

clean:
	@echo "$(RED)Cleaning $(NAME)...\n$(NC)"
	@echo "$(RED)Removing object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Cleaning libft...$(NC)"
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(RED)Cleaning mlx42...$(NC)"
	@$(MAKE) -C $(MLX42_DIR)/build clean

fclean: clean
	@echo "$(RED)Removing binary files...$(NC)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

norm:
	@norminette $(SRC_DIRS) $(INC_DIR) $(LIBFT_DIR) | grep "Error" || echo "$(GREEN)Norme OK$(NC)"

debug: CFLAGS += -g
debug: CFLAGS += -fsanitize=thread #-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=double-divide-by-zero -fsanitize=double-cast-overflow -fno-sanitize=null -fno-sanitize=alignment
debug: CFLAGS += -DDEBUG=1
debug: clean all

.PHONY: all clean fclean re norm ascii debu

# colors:
GREEN = \033[0;32m
LIGHT_GREEN = \033[0;92m
RED = \033[0;31m
YELLOW = \033[0;33m
LIGHT_YELLOW = \033[0;93m
ITALIC_LIGHT_YELLOW = \033[3;93m
CYAN = \033[0;36m
NC = \033[0m
CLEAR_LINE = \033[2K\r
ASCII_ART = $(CYAN)

# decoration:
ascii:
	@echo "------------------------------------------------"
	@echo "$(CYAN)"
	@echo "                __  ___ "
	@echo " |\/| | |\ | | |__)  |  "
	@echo " |  | | | \| | |  \  |  "
	@echo "                        "
	@echo "$(NC)"
	@echo "------------------------------------------------"

BAR_WIDTH = 50
TOTAL_SRCS = $(words $(CFILES))
