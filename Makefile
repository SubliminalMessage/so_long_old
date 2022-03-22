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

SRCS_MAND	=	mandatory/main.c \
				mandatory/errors.c \
				mandatory/parse_map.c \
				mandatory/config_map.c \
				mandatory/map_scenario.c \
				mandatory/event_results.c \
				mandatory/movement.c 

SRCS_BNS	=	bonus/main_bonus.c \
				bonus/errors_bonus.c \
				bonus/parse_map_bonus.c \
				bonus/config_map_bonus.c \
				bonus/map_scenario_bonus.c \
				bonus/event_results_bonus.c \
				bonus/movement_bonus.c 

MANDATORY_OBJS = $(SRCS_MAND:%.c=bin/%.o)
BONUS_OBJS = $(SRCS_BNS:%.c=bin/%.o)

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

$(NAME): $(MLX) $(LIBFT) $(MANDATORY_OBJS)
	@echo $(PURPLE)"[Creating $(NAME) "$(PURPLE)"]"$(WHITE)
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(LIBFT) $(MLX_FLAGS) -I $(INCS_PATH) -I $(LIBFT_PATH) -o $(NAME)

$(MLX):
	@echo $(PURPLE)"[Make MLX]"$(WHITE)
	@make -C mlx/

bonus: .bonus

.bonus: $(MLX) $(LIBFT) $(BONUS_OBJS)
	@echo $(PURPLE)"[Creating $(NAME) "$(PURPLE)"]"$(WHITE)
	@touch .bonus
	@rm -f $(NAME)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) $(MLX_FLAGS) -I $(INCS_PATH) -I $(LIBFT_PATH) -o $(NAME)

$(LIBFT):
	@echo $(PURPLE)"[Make Libft]"$(WHITE)
	@make -C $(LIBFT_PATH)

bin/mandatory/%.o: src/mandatory/%.c
	@echo $(BLUE)"[Compilation]"$(WHITE)": $< "
	@mkdir -p bin
	@mkdir -p bin/mandatory
	$(CC) $(CFLAGS) -I $(INCS_PATH) -I $(LIBFT_PATH) -I mlx/ -c $< -o $@

bin/bonus/%.o: src/bonus/%.c
	@echo $(BLUE)"[Compilation]"$(WHITE)": $< "
	@mkdir  -p bin
	@mkdir -p bin/bonus
	$(CC) $(CFLAGS) -I $(INCS_PATH) -I $(LIBFT_PATH) -I mlx/ -c $< -o $@

clean:
	@echo $(RED)"[Deleting Object Files]"$(WHITE)
	@rm -rf bin/
	@echo $(RED)"[Deleting MLX Object Files]"$(WHITE)
	@make clean -C mlx/
	@echo $(RED)"[Deleting Libft Object Files]"$(WHITE)
	@rm -f .bonus
	@make clean -C $(LIBFT_PATH)

fclean: clean 
	@echo $(RED)"[Deleting $(NAME)]"$(WHITE)
	@rm -rf $(NAME) $(MLX)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

