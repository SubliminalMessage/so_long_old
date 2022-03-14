### ---   ---   ---         ---   ---   --- ###
#             PROJECT COMPILATION             #
### ---   ---   ---         ---   ---   --- ###

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra #-g3 -fsanitize=address
MLX_FLAGS = $(MLX) -framework OpenGL -framework AppKit

# system_profiler SPDisplaysDataType | awk '/Resolution/{print $2, $3, $4}'system_profiler SPDisplaysDataType | awk '/Resolution/{print $2, $3, $4}'

MLX = mlx/libmlx.a
#DYLIB = libmlx.dylib
#MLX = mlx/$(DYLIB)

### ---   ---   ---         ---   ---   --- ###
#               PROJECT PATHS                 #
### ---   ---   ---         ---   ---   --- ###

INCS_PATH			= include/
SRCS_PATH			= src/
BIN_PATH			= bin/
LIBFT_PATH			= libft/

### ---   ---   ---         ---   ---   --- ###
#               PROJECT FILES                 #
### ---   ---   ---         ---   ---   --- ###

NAME		= so_long
LIBFT		= $(LIBFT_PATH)/libft.a

SRCS		=	main.c \
				errors.c \
				parse_map.c \
				config_map.c \
				map_scenario.c \
				event_results.c \
				movement.c 

OBJS = $(SRCS:%.c=bin/%.o)

### ---   ---   ---         ---   ---   --- ###
#              COLORS & EXTRAS :)             #
### ---   ---   ---         ---   ---   --- ###

RED		= '\033[1;31m'
GREEN	= '\033[1;32m'
PURPLE	= '\033[1;35m'
YELLOW	= '\033[1;33m'
WHITE	= '\033[1;37m'
BLUE	= '\033[1;34m'

### ---   ---   ---         ---   ---   --- ###
#                  GAME RULES                 #
### ---   ---   ---         ---   ---   --- ###

.PHONY: all re clean fclean bonus

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	@echo $(PURPLE)"[Creating $(NAME) "$(PURPLE)"]"$(WHITE)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -I $(INCS_PATH) -I $(LIBFT_PATH) -o $(NAME)

$(MLX):
	@echo $(PURPLE)"[Make MLX]"$(WHITE)
	@make -C mlx/

$(LIBFT):
	@echo $(PURPLE)"[Make Libft]"$(WHITE)
	@make -C $(LIBFT_PATH)

bin/%.o: src/%.c
	@echo $(BLUE)"[Compilation]"$(WHITE)": $< "
	@mkdir  -p bin
	$(CC) $(CFLAGS) -I $(INCS_PATH) -I $(LIBFT_PATH) -I mlx/ -c $< -o $@

clean:
	@echo $(RED)"[Deleting Object Files]"$(WHITE)
	@rm -rf bin/
	@echo $(RED)"[Deleting MLX Object Files]"$(WHITE)
	@make clean -C mlx/
	@echo $(RED)"[Deleting Libft Object Files]"$(WHITE)
	@make clean -C $(LIBFT_PATH)

fclean: clean 
	@echo $(RED)"[Deleting $(NAME)]"$(WHITE)
	@rm -rf $(NAME) $(MLX)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

