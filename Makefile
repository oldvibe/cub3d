NAME = cub3D

SRCS = main.c \
       garbage_collector.c \
       utils/utils.c \
       utils/utils2.c \
       utils/utils3.c \
       get_next_line.c \
       parsing.c \
       pars.c \
       pars_utils.c \
       pars_utils2.c \
       pars_map.c \
       pars_map_utils.c \
       raycasting.c \
       mouvement.c 

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAGS =  -L./minilibx-linux/ -lmlx -lXext -lX11 -lm
MATHFLAGS = -lm

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) $(MATHFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re