# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsavinel <bsavinel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/04 13:33:13 by bsavinel          #+#    #+#              #
#    Updated: 2022/08/12 12:56:12 by bsavinel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
########						Comilation Tools						########
################################################################################

NAME = miniRT
NAME_BONUS = miniRT_bonus

CC = cc 
CFLAGS = -g3 -O3 -Wall -Wextra -Werror -fsanitize=address

################################################################################
########							Sources 							########
################################################################################

SRCS_PATH 	=	srcs/

INCS =	$(addprefix -I ,	\
		includes			\
		libft/includes		\
		minilibx			)
		
SRCS =	end/good_exit.c						\
		mlx_utils/mlx_struct_manage.c		\
		mlx_utils/launch_loop.c				\
		mlx_utils/mlx_utils.c				\
		renderer/render.c					\
		renderer/multithreading.c			\
		math/vector.c						\
		math/tuple.c						\
		math/tuple2.c						\
		math/math_utils.c					\
		math/math_utils2.c					\
		math/matrix/matrix.c				\
		math/matrix/matrix_utils.c			\
		math/matrix/matrix_invert.c			\
		math/matrix/matrix_invert_utils.c	\
		math/matrix/matrix_transform.c		\
		lexer/file.c						\
		lexer/file_utils.c					\
		lexer/io_utils.c					\
		lexer/lexer.c						\
		lexer/lexer_utils.c					\
		lexer/lexer_utils2.c				\
		lexer/tokens.c						\
		texture/texture.c					\
		texture/texture_utils.c				\
		texture/uv_mapping.c				\
		primitives/intersect_plane.c		\
		primitives/intersect_sphere.c		\
		primitives/intersect_cone.c			\
		primitives/intersect_cylinder.c		\
		parsing/parsing.c					\
		parsing/extract_object.c			\
		parsing/extract_utils.c				\
		parsing/extract_object2.c			\
		parsing/extract_texture.c			\
		parsing/extract_utils2.c			\
		scene/object.c						\
		scene/object2.c						\
		scene/scene.c						\
		scene/camera.c						\
		shading/shading.c					\
		shading/shading_utils.c				\
		main.c								\

################################################################################
########							Libraries							########
################################################################################

LIBS =	libft/libft.a			\
		minilibx/libmlx_Linux.a	\

################################################################################
########						Objects/Dependences						########
################################################################################

OBJS_PATH =	objs/

OBJS		=	$(addprefix $(OBJS_PATH), $(SRCS:.c=.o))
OBJS_BONUS	=	$(addprefix $(OBJS_PATH), $(SRCS:.c=_bonus.o))
DEPS		=	$(addprefix $(OBJS_PATH), $(SRCS:.c=.d))

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

bonus: header $(NAME_BONUS)

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

$(NAME_BONUS) : $(LIBS) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBS) -lm -lbsd -lX11 -lXext -lpthread -o $(NAME_BONUS) $(INCS)
	echo "$(BLUE)$(NAME_BONUS): $(GREEN)Success $(NO_COLOR)"

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c Makefile
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c $< -o $@ $(INCS) -D D_BONUS=0

$(OBJS_PATH)%_bonus.o: $(SRCS_PATH)%.c Makefile
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c $< -o $@ $(INCS) -D D_BONUS=1

clean :
	$(RM) $(OBJS_PATH)
	make -C minilibx clean
	$(MAKE) -C libft clean

fclean : clean
	$(RM) $(NAME) $(NAME_BONUS)
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
