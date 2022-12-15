# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/04 13:33:13 by bsavinel          #+#    #+#              #
#    Updated: 2022/12/13 15:40:03 by plouvel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
########						Comilation Tools						########
################################################################################

NAME = miniRT_bonus

CC = cc 
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address -O3 -Ofast

################################################################################
########							Sources 							########
################################################################################

SRCS_PATH 	=	srcs/

INCS =	$(addprefix -I ,	\
		includes			\
		libft/includes		\
		minilibx			)
		
SRCS =	end/good_exit_bonus.c					\
		mlx_utils/mlx_struct_manage_bonus.c		\
		mlx_utils/launch_loop_bonus.c			\
		mlx_utils/mlx_utils_bonus.c				\
		renderer/render_bonus.c					\
		renderer/multithreading_bonus.c			\
		math/vector_bonus.c						\
		math/tuple_bonus.c						\
		math/tuple2_bonus.c						\
		math/math_utils_bonus.c					\
		math/math_utils2_bonus.c				\
		math/matrix/matrix_bonus.c				\
		math/matrix/matrix_utils_bonus.c		\
		math/matrix/matrix_invert_bonus.c		\
		math/matrix/matrix_invert_utils_bonus.c	\
		math/matrix/matrix_transform_bonus.c	\
		lexer/file_bonus.c						\
		lexer/file_utils_bonus.c				\
		lexer/io_utils_bonus.c					\
		lexer/lexer_bonus.c						\
		lexer/lexer_utils_bonus.c				\
		lexer/lexer_utils2_bonus.c				\
		lexer/tokens_bonus.c					\
		texture/texture_bonus.c					\
		texture/texture_utils_bonus.c			\
		texture/uv_mapping_bonus.c				\
		primitives/intersect_plane_bonus.c		\
		primitives/intersect_sphere_bonus.c		\
		primitives/intersect_cone_bonus.c		\
		primitives/intersect_cylinder_bonus.c	\
		parsing/parsing_bonus.c					\
		parsing/extract_object_bonus.c			\
		parsing/extract_utils_bonus.c			\
		parsing/extract_object2_bonus.c			\
		parsing/extract_texture_bonus.c			\
		parsing/extract_utils2_bonus.c			\
		scene/object_bonus.c					\
		scene/object2_bonus.c					\
		scene/scene_bonus.c						\
		scene/camera_bonus.c					\
		shading/shading_bonus.c					\
		shading/shading_utils_bonus.c			\
		main_bonus.c							\

################################################################################
########							Libraries							########
################################################################################

LIBS =	libft/libft.a			\
		minilibx/libmlx_Linux.a	\

################################################################################
########						Objects/Dependences						########
################################################################################

OBJS_PATH =	objs/

OBJS =	$(addprefix $(OBJS_PATH), $(SRCS:.c=.o))
DEPS =	$(addprefix $(OBJS_PATH), $(SRCS:.c=.d))

################################################################################
########							Others								########
################################################################################

RM = rm -rf

################################################################################
########							Colors								########
################################################################################

BLUE		=	\033[0;34m
RED			=	\033[0;31m
GREEN		=	\033[0;32m
NO_COLOR	=	\033[m

################################################################################
########							Rules								########
################################################################################

all: header $(NAME)

bonus: header all

header:
		@echo "${BLUE}"                                                       
		@echo "88b           d88  88               88  88888888ba  888888888888"
		@echo "888b         d888  \"\"               \"\"  88      \"8b      88     "
		@echo "88\`8b       d8'88                       88      ,8P      88     "
		@echo "88 \`8b     d8' 88  88  8b,dPPYba,   88  88aaaaaa8P'      88     "
		@echo "88  \`8b   d8'  88  88  88P'   \`\"8a  88  88\"\"\"\"88'        88     "
		@echo "88   \`8b d8'   88  88  88       88  88  88    \`8b        88     "
		@echo "88    \`888'    88  88  88       88  88  88     \`8b       88     "
		@echo "88     \`8'     88  88  88       88  88  88      \`8b      88     "
		@echo "                                                  by The ULTIMATE TEAM"
		@echo "${NO_COLOR}"

$(NAME) : $(LIBS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -lm -lbsd -lX11 -lXext -lpthread -o $(NAME) $(INCS)
	echo "$(BLUE)$(NAME): $(GREEN)Success $(NO_COLOR)"

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c Makefile
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c $< -o $@ $(INCS) -D D_BONUS=1

clean :
	$(RM) $(OBJS_PATH)
	make -C minilibx clean
	$(MAKE) -C libft clean

fclean : clean
	$(RM) $(NAME) 
	$(RM) libft/libft.a

re : fclean 
	make -C minilibx re
	make all

################################################################################
#######							Rules for libs							########
################################################################################

libft/libft.a :
	$(MAKE) -C libft all && echo "$(BLUE)Compiation of libft: $(GREEN)Success $(NO_COLOR)" || echo "$(BLUE)Compiation of libft: $(RED)Fail $(NO_COLOR)"

minilibx/libmlx_Linux.a:
	make -C minilibx all && echo "$(BLUE)Compiation of minilibx: $(GREEN)Success $(NO_COLOR)" || echo "$(BLUE)Compiation of libft: $(RED)Fail $(NO_COLOR)"

-include $(DEPS)

.PHONY: all clean fclean re bonus

.SILENT:
