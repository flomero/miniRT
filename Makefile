# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 18:35:04 by flfische          #+#    #+#              #
#    Updated: 2024/06/09 15:27:54 by klamprak         ###   ########.fr        #
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


OBJ_DIR := obj
INC_DIR := includes
TMP_DIR := tmp

# FILES
vpath %.c $(SRC_DIRS)
vpath %.h $(INC_DIR)

CFILES := miniRT.c \
			mlx_init.c \
			mlx_hooks.c \
			print_error.c \
			parsing.c \
			parsing_handlers.c \


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
debug: CFLAGS += -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment
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
