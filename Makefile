# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/23 11:53:39 by miduarte          #+#    #+#              #
#    Updated: 2025/06/23 12:37:51 by miduarte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = so_long

SRCS    = main.c map.c player.c render.c utils.c
OBJS    = $(SRCS:.c=.o)

CC      = cc
CFLAGS  = -Wall -Wextra -Werror

MLX_DIR = ./minilibx-linux
MLX     = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

RM      = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re