# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/23 11:53:39 by miduarte          #+#    #+#              #
#    Updated: 2025/07/09 11:22:39 by miduarte         ###   ########.fr        #
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
PRINTF_DIR = ./ft_printf
MLX     = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

RM      = rm -f

# Add printf.a as a dependency and link it
PRINTF_A = $(PRINTF_DIR)/libftprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF_A)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) -L$(PRINTF_DIR) -lftprintf

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(GNL_DIR) -I$(PRINTF_DIR) -c $< -o $@

# Build ft_printf library
$(PRINTF_A):
	$(MAKE) -C $(PRINTF_DIR)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re