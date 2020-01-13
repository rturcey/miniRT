NAME = miniRT

SOURCES = ./sources/basics.c \
		./sources/colors.c \
		./sources/colors2.c \
		./sources/cones.c \
		./sources/cylinders.c \
		./sources/effects.c \
		./sources/exportbmp.c \
		./sources/hook.c \
		./sources/hook2.c \
		./sources/inter.c \
		./sources/launch.c \
		./sources/mapping.c \
		./sources/minirt.c \
		./sources/minirt_lite.c \
		./sources/pyracubes.c \
		./sources/rays.c \
		./sources/squares.c \
		./sources/parsing/parsing.c \
		./sources/parsing/parsing_cams.c \
		./sources/parsing/parsing_composed.c \
		./sources/parsing/parsing_effects.c \
		./sources/parsing/parsing_lights.c \
		./sources/parsing/parsing_objs.c \
		./sources/parsing/parsing_simple.c \
		./sources/parsing/parsing_textures.c \
		./sources/parsing/parsing_utils.c

OBJECTS = $(SOURCES:.c=.o)

LIBFT = ./libft/libft.a

INCLUDES = -I ./includes/

COMPILER = gcc -c

FLAGS = -Wall -Wextra -Werror

FLAGS_MLX = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJECTS)
	make -C ./libft
	gcc $(OBJECTS) $(FLAGS) $(FLAGS_MLX) $(LIBFT) -o $(NAME)

%.o: %.c
	$(COMPILER) -o $@ $< $(FLAGS) $(INCLUDES)
	
clean:
	make clean -C ./libft
	rm -rf $(OBJECTS)

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re: fclean all
	make re -C ./libft