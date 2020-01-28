NAME = miniRT
INCLUDES = -I ./includes/
SOURCES = ./sources/basics.c ./sources/colors.c ./sources/colors2.c ./sources/cones.c \
		./sources/cylinders.c ./sources/effects.c ./sources/exportbmp.c ./sources/inter.c \
		./sources/launch.c ./sources/mapping.c ./sources/minirt.c ./sources/minirt_lite.c \
		./sources/pyracubes.c ./sources/utils.c ./sources/squares.c ./sources/interactions/hook_transformations.c \
		./sources/interactions/hook_keys.c ./sources/interactions/hook_mousemotion.c \
		./sources/parsing/parsing.c ./sources/parsing/parsing_cams.c ./sources/parsing/parsing_cp.c \
		./sources/parsing/parsing_effects.c ./sources/parsing/parsing_lights.c ./sources/parsing/parsing_objs.c \
		./sources/parsing/parsing_simple.c ./sources/parsing/parsing_textures.c ./sources/parsing/parsing_utils.c \
		./sources/parsing/parsing_utils2.c ./sources/parsing/parsing_utils3.c ./includes/vectors/vectors.c \
		./includes/vectors/vectors2.c ./includes/vectors/vecrot.c

OBJECTS = $(SOURCES:.c=.o)

LIBFT = ./libft/libft.a

MLX = ./mlx/libmlx.a

COMPILER = gcc -c

FLAGS = -Wall -Wextra -Werror

FLAGS_MLX = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJECTS)
	make -C ./libft
	make -C ./mlx
	gcc $(OBJECTS) $(FLAGS) $(FLAGS_MLX) $(LIBFT) $(MLX) -o $(NAME)

%.o: %.c
	$(COMPILER) -o $@ $< $(FLAGS) $(INCLUDES)
	
clean:
	make clean -C ./libft
	make clean -C ./mlx
	rm -rf $(OBJECTS)

fclean: clean
	make fclean -C ./libft
	make fclean -C ./mlx
	rm -rf $(NAME)

re: fclean all
	make re -C ./libft
	make re -C ./mlx