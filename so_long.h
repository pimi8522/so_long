/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:59 by miduarte          #+#    #+#             */
/*   Updated: 2025/06/24 16:37:37 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx-linux/mlx.h"
#include "./minilibx-linux/mlx_int.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>

typedef struct s_imgs {
	void *idle[2];
	void *run[8];
}	t_imgs;

typedef struct s_data {
	void *img;
	char *adr;
	int bits_per_pixel;
	int line_length;
	int endian;
}	t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_data	img;
	t_imgs  *sprites;
	int		frame;
	int		pos_x;
	int		pos_y;
}	t_vars;

