NAME        = cub3D

CC          = cc
CFLAGS      = #-Wall -Wextra -Werror -g

MLX_DIR     = minilibx_opengl
MLX_FLAGS   = -L/usr/include/minilibx-linux -lmlx -lXext -lX11 -lm
MLX         = $(MLX_DIR)/libmlx.a

INCLUDES    = -I includes

OBJ_DIR     = objects

MAIN_SRC = \
    sources/main.c \
    sources/maze/eternal_maze.c \
    sources/maze/maze_struct.c \
    sources/maze/maze_setup.c \
    sources/maze/load_textures.c \
    sources/maze/destroy_maze.c \
    sources/init/init_maze.c \
    sources/init/init_structs.c \
    sources/init/file_validity.c \
    sources/hooks/hooks.c \
    sources/parser/config_parser.c \
    sources/parser/map_validity.c \
    sources/parser/map_extractor.c \
    sources/parser/env_extractor.c \
    sources/parser/rgb_resolution.c \
    sources/parser/player.c \
    sources/errors/error.c \
    sources/render/render.c \
    sources/render/minimap.c \
    sources/render/rays.c

ALLOC_SRC = \
    memtrack/smalloc.c \
    memtrack/clear_data.c \
    memtrack/destroy_all.c \
    memtrack/find_sections.c \
    memtrack/add_allocation.c \
    memtrack/new_allocation.c \
    memtrack/create_section.c \
    memtrack/current_section.c \
    memtrack/destroy_section.c \
    memtrack/free_one_pointer.c \
    memtrack/safe_open.c \
    memtrack/clean_before_prompt.c

UTILS_SRC = \
    utils/read_file.c \
    utils/count_char.c \
    utils/skip_spaces.c \
    utils/split_lines.c \
    utils/split_one_time.c \
    utils/check_if_match.c \
    utils/join_two_strings.c


# remove none used functions
STDFCTS_SRC = \
    stdfcts/ft_min.c \
    stdfcts/ft_abs.c \
    stdfcts/ft_itoa.c \
    stdfcts/ft_atoi.c \
    stdfcts/ft_split.c \
    stdfcts/ft_numlen.c \
    stdfcts/ft_substr.c \
    stdfcts/ft_strcmp.c \
    stdfcts/ft_strchr.c \
    stdfcts/ft_memset.c \
    stdfcts/ft_memcpy.c \
    stdfcts/ft_strcat.c \
    stdfcts/ft_strlen.c \
    stdfcts/ft_strrchr.c \
    stdfcts/ft_isspace.c \
    stdfcts/ft_strjoin.c \
    stdfcts/ft_isalnum.c \
    stdfcts/ft_isalpha.c \
    stdfcts/ft_strndup.c \
    stdfcts/ft_strncmp.c \
    stdfcts/ft_isdigit.c \
    stdfcts/ft_realloc.c

SRCS = $(MAIN_SRC) $(UTILS_SRC) $(STDFCTS_SRC) $(ALLOC_SRC)


OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))


VPATH = utils:\
        sources:\
        stdfcts:\
        memtrack:\
        sources/init:\
        sources/maze:\
        sources/hooks:\
        sources/render\
        sources/parser:\
        sources/errors:

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS) 
	# @$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS)  $(MLX_FLAGS) -o $(NAME)


$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -rf $(OBJ_DIR)
	# @$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
