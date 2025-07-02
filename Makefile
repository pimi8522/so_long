# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/23 11:53:39 by miduarte          #+#    #+#              #
#    Updated: 2025/06/25 12:03:59 by miduarte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = so_long

SRCS    = main.c map.c player.c render.c utils.c
GNL_DIR = ./get_next_line
GNL_SRCS = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
OBJS    = $(SRCS:.c=.o) $(GNL_SRCS:.c=.o)

CC      = cc
CFLAGS  = -Wall -Wextra -Werror

MLX_DIR = ./minilibx-linux
MLX     = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

RM      = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(GNL_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re