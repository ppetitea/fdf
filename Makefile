NAME		= fdf

# Sources
SRC		= main.c\
			./sources/hook.c\
			./sources/move.c\
			./sources/draw.c\
			./sources/copy_map.c\
			./sources/parse.c\
			./sources/bresenham.c\
			./sources/manage_error.c\
			./sources/transformation.c\
			./sources/callback.c

UNAME =	$(shell uname)

LIBFT_FOLDER	= libft

ifeq ($(UNAME), Linux)
MLX_FOLDER	= minilibx
LIB_FOLDERS	= -L$(MLX_FOLDER) -L$(LIBFT_FOLDER) -L/usr/X11/lib
LIBS		= -lmlx -lft -lXext -lX11 -lm
LDFLAGS		=
else
MLX_FOLDER	= minilibx_macos
LIB_FOLDERS	= -L$(MLX_FOLDER) -L$(LIBFT_FOLDER)
LIBS		= -lmlx -lft
LDFLAGS		= -framework OpenGL -framework AppKit
endif

# Compilation
CXX		= gcc
CFLAGS		= -Wall -Wextra -Werror -O3
INCLUDES	= -I includes -I $(MLX_FOLDER) -I $(LIBFT_FOLDER)

# Linking
OBJ		= $(SRC:.c=.o)

# Colors
GREEN		= \033[32m
RESET		= \033[0m

all: libft mlx $(NAME)

$(NAME): $(OBJ)
	@printf "$(GREEN)[cc]$(RESET): done\n"
	@printf "$(GREEN)[ld]$(RESET): $(NAME)\n"
	@$(CXX) -o $(NAME) $(OBJ) $(LIB_FOLDERS) $(LIBS) $(LDFLAGS) $(INCLUDES) -g

.c.o : $(SRC) 
	@printf "$(GREEN)[cc]$(RESET): $< -> $@\n"
	@printf "\e[1A"
	@gcc -c $< -o $@ $(INCLUDES) $(CFLAGS)
	@printf "\e[0K"

run: all
	@./$(NAME)

libft:
	@printf "$(GREEN)[mk]$(RESET): libft all\n"
	@make -C libft
	@printf "\e[1A\e[0K"
	@printf "$(GREEN)[mk]$(RESET): libft all done\n"

libft-clean:
	@printf "$(GREEN)[mk]$(RESET): libft clean\n"
	@make -C $(LIBFT_FOLDER) clean >/dev/null
	@printf "\e[1A\e[0K"
	@printf "$(GREEN)[mk]$(RESET): libft clean done\n"

libft-fclean:
	@printf "$(GREEN)[mk]$(RESET): libft fclean\n"
	@make -C $(LIBFT_FOLDER) fclean >/dev/null
	@printf "\e[1A\e[0K"
	@printf "$(GREEN)[mk]$(RESET): libft fclean done\n"

libft-re:
	@printf "$(GREEN)[mk]$(RESET): libft re\n"
	@make -C $(LIBFT_FOLDER) re
	@printf "\e[1A\e[0K"
	@printf "$(GREEN)[mk]$(RESET): libft re done\n"

mlx:
	@printf "$(GREEN)[mk]$(RESET): mlx all\n"
	@make -C $(MLX_FOLDER) &>/dev/null
	@printf "\e[1A\e[0K"
	@printf "$(GREEN)[mk]$(RESET): mlx all done\n"

mlx-clean:
	@printf "$(GREEN)[mk]$(RESET): mlx clean\n"
	@make -C $(MLX_FOLDER) clean &>/dev/null
	@printf "\e[1A\e[0K"
	@printf "$(GREEN)[mk]$(RESET): mlx clean done\n"

mlx-fclean: mlx-clean
	@printf "$(GREEN)[mk]$(RESET): mlx fclean\n"
	@rm -rf $(MLX_FOLDER)/libmlx.a
	@printf "\e[1A\e[0K"
	@printf "$(GREEN)[mk]$(RESET): mlx fclean done\n"

mlx-re:
	@printf "$(GREEN)[mk]$(RESET): mlx re\n"
	@make -C $(MLX_FOLDER) re &>/dev/null
	@printf "\e[1A\e[0K"
	@printf "$(GREEN)[mk]$(RESET): mlx re done\n"

clean: libft-clean mlx-clean
	@printf "$(GREEN)[rm]$(RESET): cleaned object files\n"
	@rm -rf $(OBJ)

fclean: clean libft-fclean mlx-fclean
	@printf "$(GREEN)[rm]$(RESET): cleaned binary file\n"
	@rm -rf $(NAME)

re: fclean libft mlx all

.PHONY: all $(NAME) norm libft libft-clean libft-fclean libft-re mlx mlx-clean \
		mlx-fclean mlx-re clean fclean re
